#!/usr/bin/env python3
"""Compile Markdown to PDF, optionally omitting exercise answers.

Answer blocks are removed in questions-only mode when marked like this:

<!-- answer:start -->
answer text
<!-- answer:end -->
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ANSWER_START = "<!-- answer:start -->"
ANSWER_END = "<!-- answer:end -->"


def strip_answer_blocks(text: str) -> str:
    lines = text.splitlines()
    output: list[str] = []
    skipping = False
    removed_blocks = 0

    for line in lines:
        if line.strip() == ANSWER_START:
            if skipping:
                raise ValueError("nested answer block marker found")
            skipping = True
            removed_blocks += 1
            continue

        if line.strip() == ANSWER_END:
            if not skipping:
                raise ValueError("answer end marker without matching start marker")
            skipping = False
            continue

        if not skipping:
            output.append(line)

    if skipping:
        raise ValueError("answer block was not closed")

    if removed_blocks == 0:
        print("warning: no answer blocks found", file=sys.stderr)

    return "\n".join(output).strip() + "\n"


def insert_question_page_breaks(text: str) -> str:
    """Start every level-2 Question section after the first on a new page."""
    output: list[str] = []
    seen_question = False

    for line in text.splitlines():
        if line.startswith("## Question"):
            if seen_question:
                while output and output[-1] == "":
                    output.pop()
                output.extend(["", r"\newpage", ""])
            seen_question = True
        output.append(line)

    return "\n".join(output).strip() + "\n"


def default_output_path(markdown_path: Path, mode: str) -> Path:
    suffix = "_questions.pdf" if mode == "questions" else "_questions_and_answers.pdf"
    return markdown_path.with_name(markdown_path.stem + suffix)


def compile_pdf(markdown_path: Path, output_path: Path, mode: str) -> None:
    pandoc = shutil.which("pandoc")
    if not pandoc:
        raise RuntimeError("pandoc was not found in PATH")

    pdf_engine = shutil.which("xelatex") or shutil.which("lualatex") or shutil.which("pdflatex")
    if not pdf_engine:
        raise RuntimeError("no LaTeX PDF engine found; install xelatex, lualatex, or pdflatex")

    text = markdown_path.read_text(encoding="utf-8")
    if mode == "questions":
        text = strip_answer_blocks(text)
    text = insert_question_page_breaks(text)

    output_path.parent.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix="markdown-pdf-") as tmpdir:
        prepared = Path(tmpdir) / markdown_path.name
        prepared.write_text(text, encoding="utf-8")

        command = [
            pandoc,
            str(prepared),
            "--standalone",
            "--pdf-engine",
            pdf_engine,
            "--resource-path",
            os.pathsep.join([str(markdown_path.parent.resolve()), str(Path.cwd().resolve())]),
            "-V",
            "geometry:margin=1in",
            "-V",
            "fontsize=11pt",
            "-V",
            "colorlinks=true",
            "-o",
            str(output_path),
        ]
        subprocess.run(command, check=True)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Compile Markdown to PDF, with optional questions-only mode for exercise files."
    )
    parser.add_argument("markdown", type=Path, help="Input Markdown file")
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        help="Output PDF path. Defaults to INPUT.pdf or INPUT_questions.pdf.",
    )
    parser.add_argument(
        "--mode",
        choices=("questions", "questions-and-answers"),
        default="questions-and-answers",
        help="Use 'questions' to omit marked answer blocks, or 'questions-and-answers' to include them.",
    )
    args = parser.parse_args()

    markdown_path = args.markdown
    if not markdown_path.is_file():
        parser.error(f"input Markdown file not found: {markdown_path}")

    output_path = args.output or default_output_path(markdown_path, args.mode)
    compile_pdf(markdown_path, output_path, args.mode)
    print(output_path)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
