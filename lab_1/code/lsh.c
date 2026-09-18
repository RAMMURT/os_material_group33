/*
 * Main source file for the lsh shell program.
 *
 * You are free to add functions to this file.
 * If you want to add functions in separate files,
 * you will need to modify CMakeLists.txt to compile
 * your additional files.
 *
 * Add appropriate comments to make your code
 * easier for us to grade.
 *
 * Using assert statements is a good way to catch errors early and make debugging easier.
 * Think of them as mini self-checks that ensure your program behaves as expected.
 * By setting up these guardrails, you're creating a more robust and maintainable solution.
 * So go ahead, sprinkle some asserts in your code; they're your friends in disguise!
 *
 * All the best!
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

// The <unistd.h> header is your gateway to the OS's process management facilities.
#include <unistd.h>

#include "parse.h"

static void INThandler(int sig);
static void handle_cmd(Command *cmd);
static void print_cmd(Command *cmd);
static void print_pgm(Pgm *p);
void stripwhite(char *);

const int READ = 0;
const int WRITE = 1;

int foregroundPID = -1;

int main(void)
{
  // Handle SIGINT
  signal(SIGINT, INThandler);
  // Ignore child processes to prevent zombies
  signal(SIGCHLD, SIG_IGN);

  for (;;)
  {
    printf("\e[0;32m%s\e[0m:\e[0;36m%s\e[0m", getlogin(), getcwd(NULL, 0));
    char *line;
    line = readline("> ");

    // Handle Ctrl+D
    if (line == NULL) {
      free(line);
      break;
    }

    // Remove leading and trailing whitespace from the line
    stripwhite(line);

    // If the stripped line is not blank
    if (*line)
    {
      // Detect "exit" command
      if (strcmp(line, "exit") == 0) {
        exit(0);
      }

      add_history(line);

      Command cmd;
      if (parse(line, &cmd) == 1)
      {
        handle_cmd(&cmd);
      }
      else
      {
        printf("Parse ERROR\n");
      }
    }

    // Free the input buffer
    free(line);
  }

  return 0;
}

static void INThandler(int sig) {
  // Ignore SIGINT
  signal(SIGINT, SIG_IGN);

  // No foreground process? Exit shell
  if (foregroundPID < 0) {
    exit(SIGINT);
    return;
  }

  // Kill foreground process
  kill(foregroundPID, SIGINT);
  printf("\n");
  foregroundPID = -1;

  // Re-install SIGINT handler
  signal(SIGINT, INThandler);
}

static int nr_programs(Command *cmd) {
  int count = 0;
  Pgm *currentProgram = cmd->pgm;
  while (currentProgram != NULL) {
    count++;
    currentProgram = currentProgram->next;
  }
  return count;
}

static void handle_cmd(Command *cmd) {
  // // Print the parsed command
  // print_cmd(cmd);

  // Handle "cd"
  char **args = cmd->pgm->pgmlist;
  if (cmd->pgm->next == NULL && strcmp(args[0], "cd") == 0) {
    if (args[2] != NULL) {
      printf("cd: too many arguments\n");
      return;
    }
    chdir(args[1]);
    return;
  }

  // Create n - 1 pipes
  int nrPipes = nr_programs(cmd) - 1;
  int pipes[2 * nrPipes];
  for (int i = 0; i < nrPipes; i++) {
    if (pipe(pipes + i * 2) < 0) {
      printf("Pipe creation failed!\n");
      return;
    }
  }

  int idx = 0;
  Pgm *currentProgram = cmd->pgm;
  while (currentProgram != NULL) {
    int pid = fork();
    if (pid == -1) {
      printf("Fork failed\n");
      return;
    }

    // Child
    if (pid == 0) {
      int saved_stdout = dup(STDOUT_FILENO);

      // Connect STDOUT to write pipe
      if (idx - 1 >= 0) {
        close(pipes[(idx - 1) * 2 + READ]);
        dup2(pipes[(idx - 1) * 2 + WRITE], STDOUT_FILENO);
      }
      else if (cmd->rstdout != NULL) {
        int fd = open(cmd->rstdout, O_WRONLY | O_CREAT, 0644);
        dup2(fd, STDOUT_FILENO);
      }

      // Connect STDIN to read pipe
      if (idx < nrPipes) {
        dup2(pipes[idx * 2 + READ], STDIN_FILENO);
        close(pipes[idx * 2 + WRITE]);
      }
      else if (cmd->rstdin != NULL) {
        int fd = open(cmd->rstdin, 0);
        dup2(fd, STDIN_FILENO);
      }

      // Close all pipes except the two connected to this child
      for (int i = 0; i < nrPipes; i++) {
        if (i != idx - 1 && i != idx) {
          close(pipes[i * 2 + READ]);
          close(pipes[i * 2 + WRITE]);
        }
      }

      if (cmd->background) {
        // Print PID of background process
        printf("PID: %d\n", getpid());
        // Prevent background process from accessing terminal I/O
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        close(STDIN_FILENO);
        // Ignore SIGINT
        signal(SIGINT, SIG_IGN);
      }

      // Execute command
      char **list = currentProgram->pgmlist;
      execvp(list[0], list);

      // Restore stdout
      dup2(saved_stdout, STDOUT_FILENO);
      printf("Error in child process: %s\n", list[0]);
      exit(1);
    }
    // Parent
    else {
      // Store pid so it can be SIGINT'ed
      if (!cmd->background) {
        foregroundPID = pid;
      }
    }
    
    idx++;
    currentProgram = currentProgram->next;
  }

  // Close all pipes in parent as they are not needed
  for (int i = 0; i < nrPipes; i++) {
    close(pipes[i * 2 + READ]);
    close(pipes[i * 2 + WRITE]);
  }
  // Wait for all foreground processes
  if (!cmd->background) {
    for (int i = 0; i < nrPipes + 1; i++) {
      wait(NULL);
    }
  }
  foregroundPID = -1;
}

/*
 * Print a Command structure as returned by parse on stdout.
 *
 * Helper function, no need to change. Might be useful to study as inspiration.
 */
static void print_cmd(Command *cmd_list)
{
  printf("------------------------------\n");
  printf("Parse OK\n");
  printf("stdin:      %s\n", cmd_list->rstdin ? cmd_list->rstdin : "<none>");
  printf("stdout:     %s\n", cmd_list->rstdout ? cmd_list->rstdout : "<none>");
  printf("background: %s\n", cmd_list->background ? "true" : "false");
  printf("Pgms:\n");
  print_pgm(cmd_list->pgm);
  printf("------------------------------\n");
}

/* Print a linked list of Pgm structures.
 *
 * Helper function, no need to change. It may be useful to study for inspiration.
 */
static void print_pgm(Pgm *p)
{
  if (p == NULL)
  {
    return;
  }
  else
  {
    char **pl = p->pgmlist;

    /* The list is stored in reverse order, so print
     * it in reverse to restore the original order.
     */
    print_pgm(p->next);
    printf("            * [ ");
    while (*pl)
    {
      printf("%s ", *pl++);
    }
    printf("]\n");
  }
}


/* Strip whitespace from the start and end of a string.
 *
 * Helper function, no need to change.
 */
void stripwhite(char *string)
{
  size_t i = 0;

  while (isspace(string[i]))
  {
    i++;
  }

  if (i)
  {
    memmove(string, string + i, strlen(string + i) + 1);
  }

  i = strlen(string) - 1;
  while (i > 0 && isspace(string[i]))
  {
    i--;
  }

  string[++i] = '\0';
}
