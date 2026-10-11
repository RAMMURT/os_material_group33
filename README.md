# Operating Systems Course Material

This repository contains teaching material for the Operating Systems course EDA093/DIT401. It includes video lectures, subtitles/transcripts, and slide decks.

## Repository Contents

- Topic folders such as `processes/`, `threads/`, and `virtual_memory/` contain the video lectures (`.mp4`), matching subtitles (`.srt`), and the corresponding slide decks, usually as both editable `.pptx` files and exported `.pdf` files.
- `other_slides/` contains slide decks that are not tied to a specific video lecture, such as the course introduction and conclusion.
- For most lectures, the last slides contain questions that can be used to assess students' understanding during live discussions. Answers are given in the notes section of the PowerPoint files.
- Some topic folders also contain exam questions and answers in Markdown format. These files can be compiled into PDFs either with answers or as questions only.
- `overview.xlsx` is the source overview used for the suggested lecture order below.

The `.mp4` files are tracked with Git LFS. After cloning, run `git lfs pull` if the videos are missing or appear as pointer files.

## Suggested Order

The order below is the suggested order for the various lectures. For each lecture, use the matching slide deck and watch the numbered videos in the corresponding topic folder. For your convenience, you can also find below links to YouTube playlists that contain the same videos. Please, send me a mail if some video is wrong / has wrong or misaligned subtitles.

| Order | Lecture | Folder | Slides | Link (YouTube playlist) |
| --- | --- | --- | --- | --- |
| 01 | Introduction | [`introduction_os/`](introduction_os/) | [`pdf`](introduction_os/introduction_os.pdf), [`pptx`](introduction_os/introduction_os.pptx) | https://www.youtube.com/playlist?list=PLNP2wHlXPxGs |
| 02 | Processes | [`processes/`](processes/) | [`pdf`](processes/processes.pdf), [`pptx`](processes/processes.pptx) | https://www.youtube.com/playlist?list=PLdKN6j-dCZb0 |
| 03 | Multithreaded Programming | [`threads/`](threads/) | [`pdf`](threads/threads.pdf), [`pptx`](threads/threads.pptx) | https://www.youtube.com/playlist?list=PLSL2B2hUh7xo |
| 04 | Process Scheduling | [`process_scheduling/`](process_scheduling/) | [`pdf`](process_scheduling/process_scheduling.pdf), [`pptx`](process_scheduling/process_scheduling.pptx) | https://www.youtube.com/playlist?list=PLDtjXc-5M71M |
| 05 | Synchronization - Part 1 | [`synchronization_part_1/`](synchronization_part_1/) | [`pdf`](synchronization_part_1/synchronization_part_1.pdf), [`pptx`](synchronization_part_1/synchronization_part_1.pptx) | https://www.youtube.com/playlist?list=PLG8eRVzYTT1U |
| 06 | Synchronization - Part 2 | [`synchronization_part_2/`](synchronization_part_2/) | [`pdf`](synchronization_part_2/synchronization_part_2.pdf), [`pptx`](synchronization_part_2/synchronization_part_2.pptx) | https://www.youtube.com/playlist?list=PLDwUGWNT5DeI |
| 07 | Memory Management | [`memory_management/`](memory_management/) | [`pdf`](memory_management/memory_management.pdf), [`pptx`](memory_management/memory_management.pptx) | https://www.youtube.com/playlist?list=PLSX1pbp9RzZ4 |
| 08 | Virtual Memory | [`virtual_memory/`](virtual_memory/) | [`pdf`](virtual_memory/virtual_memory.pdf), [`pptx`](virtual_memory/virtual_memory.pptx) | https://www.youtube.com/playlist?list=PLes0bMzQDLbU |
| 09 | File Systems | [`file_system/`](file_system/) | [`pdf`](file_system/file_systems.pdf), [`pptx`](file_system/file_systems.pptx) | https://www.youtube.com/playlist?list=PLXjfl1TCxXHk |
| 10 | Security | [`security/`](security/) | [`pdf`](security/security.pdf), [`pptx`](security/security.pptx) | https://www.youtube.com/playlist?list=PLSdxAi6R1GFc |
| 11 | I/O Systems | [`io_system/`](io_system/) | [`pdf`](io_system/io_systems.pdf), [`pptx`](io_system/IO_systems.pptx) | https://www.youtube.com/playlist?list=PLCxd6fxIcgqQ |
| 12 | Virtualization | [`virtualization/`](virtualization/) | [`pdf`](virtualization/virtualization.pdf), [`pptx`](virtualization/virtualization.pptx) | https://www.youtube.com/playlist?list=PLFTGTnFYUFwU |

Additional slide-only decks are available for the course introduction and conclusion in `other_slides/`:

- [`course_introduction.pdf`](other_slides/course_introduction.pdf) / [`course_introduction.pptx`](other_slides/course_introduction.pptx)
- [`conclusion.pdf`](other_slides/conclusion.pdf) / [`conclusion.pptx`](other_slides/conclusion.pptx)

## Exam Questions

Some folders contain Markdown files with exam questions and answers, for example:

- [`processes/processes_exam_questions_answers.md`](processes/processes_exam_questions_answers.md)
- [`threads/threads_exam_questions_answers.md`](threads/threads_exam_questions_answers.md)
- [`process_scheduling/process_scheduling_exam_questions_answers.md`](process_scheduling/process_scheduling_exam_questions_answers.md)

These Markdown files can be compiled into PDFs with [`scripts/compile_markdown_pdf.py`](scripts/compile_markdown_pdf.py). Use `--mode questions-and-answers` to include answers, or `--mode questions` to produce a PDF with questions only.

For example:

```bash
python3 scripts/compile_markdown_pdf.py processes/processes_exam_questions_answers.md --mode questions-and-answers
python3 scripts/compile_markdown_pdf.py processes/processes_exam_questions_answers.md --mode questions
```

By default, the generated PDF is saved next to the Markdown file. Use `-o` to choose a specific output path:

```bash
python3 scripts/compile_markdown_pdf.py threads/threads_exam_questions_answers.md --mode questions -o threads/threads_exam_questions.pdf
```

## Video Part Order

### 01. Introduction

1. Introduction
2. System calls
3. Services
4. OS structures

### 02. Processes

1. Introduction
2. Context switches
3. Process information
4. Scheduling
5. `fork`/`exec`
6. Inter-process communication
7. Pipes

### 03. Multithreaded Programming

1. Introduction
2. Multithreaded processes
3. Concurrent vs. parallel execution
4. Amdahl's Law
5. Multithreading models
6. Pthreads
7. Implicit threading
8. Threading issues

### 04. Process Scheduling

1. Introduction and CPU-bound vs. I/O-bound processes
2. Scheduling goals in batch systems
3. Scheduling goals in interactive systems
4. Continued discussion on user-level and kernel-level threads
5. Multiprocessor challenges, part 1
6. Multiprocessor challenges, part 2
7. Multiprocessor scheduling

### 05. Synchronization - Part 1

1. Introduction
2. Critical section / check-completion approach
3. Check-order / after-you approach
4. Peterson's algorithm
5. Hardware support / RMW instructions
6. Semaphores
7. Other synchronization techniques

### 06. Synchronization - Part 2

1. Bounded-buffer producer/consumer
2. Resource allocation, deadlocks, and conditions for deadlocks
3. Dining philosophers
4. Dining philosophers - no circular wait
5. Dining philosophers - no no-preemption
6. Dining philosophers - no hold-and-wait
7. Lamport's bakery algorithm
8. Readers/writers
9. Deadlock avoidance

### 07. Memory Management

1. Introduction
2. Base/limit registers
3. Logical/physical addresses
4. Swapping
5. Contiguous allocation
6. Segmentation
7. Paging

### 08. Virtual Memory

1. Introduction
2. Page faults
3. Copy-on-write
4. Page replacement, part 1
5. Page replacement, part 2
6. Allocation of frames
7. Thrashing

### 09. File Systems

1. Introduction
2. Access methods and blocks
3. Disk structure
4. File system structure
5. Allocation methods
6. Free space
7. File sharing and protection

### 10. Security

1. Introduction
2. Protection domains
3. Access control lists
4. Capabilities
5. Authentication
6. Buffer overflow attacks

### 11. I/O Systems

1. Introduction
2. Bus structure
3. Communication ways
4. Interrupts
5. DMA
6. Application I/O interface
7. Kernel I/O subsystem
8. Performance

### 12. Virtualization

1. Introduction
2. Requirements for virtualization
3. Types of hypervisors
4. Efficient virtualization
5. Memory virtualization
6. I/O virtualization
7. Other benefits
8. Virtualization and clouds
9. Containers

## Course literature and reading instructions

The material is mainly based on the book *Modern Operating Systems* by Andrew S. Tanenbaum (fifth edition). The following list contains the parts to be read to complement what is presented in the videos and slides.

- Lecture 01, introduction: Chapter 1, especially 1.1, 1.3, 1.6 and 1.7
- Lecture 02, processes: Chapter 2.1 
- Lecture 03, threads: Chapter 2.2, 10.3.3 (some concepts are covered later on, like for Copy-on-Write)
- Lecture 04, scheduling: Chapter 2.4, 8.1.1, 8.1.2, 8.1.4, 10.3.4, 11.4.1
- Lectures 05 and 06, synchronization: Chapter 2.4.1-2.4.6, 6.1-6.2, 6.5-6.6, 6.7.3-6.7.4; Quicker reading, for awareness, of sections 2.3.7-2.3.9, 2.3.11, 6.3
- Lecture 07, memory management: Chapter 3.1, 3.2, 3.7 (up to 3.7.1 - excluded)
- Lecture 08, virtual memory: Chapter 3.3-3.6.
- Lecture 09, file systems: Chapter 4.1 to 4.4
- Lecture 10, security: Chapter 9, from the beginning until 9.4.1 (only the first paragraph of 9.4.1); 9.6 to 9.7.1 (only up to Data Execution Prevention - included); 9.9.3; The Sony Rootkit (starts at page 683, part of 9.9.5)
- Lecture 11, I/O systems: Chapter 5.1-5.3
- Lecture 12, virtualization: Chapter 7, 7.1-7.10 (included)

## Acknowledgement

This material is prepared for teaching purposes and builds on standard operating systems textbooks, in particular *Modern Operating Systems* by Andrew S. Tanenbaum and Herbert Bos, and *Operating System Concepts* by Abraham Silberschatz, Peter Baer Galvin, and Greg Gagne. Some figures, examples, and exercises used in the slides and supporting material are adapted from or inspired by these books. They remain the work of their respective authors and publishers; they are included here only to support the course and are not claimed as original material.
