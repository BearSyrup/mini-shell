#include "../headers/mini.h"
#include "../headers/command_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char *sh_readline() {
  char *buffer;
  int position;
  int c;

  buffer = malloc(BUFSIZE * sizeof(char));
  if (!buffer) {
    fprintf(stderr, "minish: allocator error");
    exit(1);
  }

  position = 0;
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    }
    buffer[position++] = c;
  }
  return buffer;
}

void sh_exec(char *command) {
  char *file_path;
  char **args;
  int status;
  command_list *commands;
  char delim[2] = {' ', '\0'};

  commands = split_command_list(command);

  if (strcmp(commands->command, "exit") == 0) {
    exit(0);
  }

  while (commands != NULL) {
    args = split(commands->command, delim);
    if (strcmp(args[0], "cd") == 0) {
      status = go_directory(args[1]);
      return;
    }

    file_path = fpath(args[0]);
    status = command_exec(file_path, args);
    commands = commands->next;
  }

  free(file_path);
  free(args);
}

int command_exec(char *file_path, char **args) {
  int pid;
  int status;

  pid = fork();
  if (pid == -1) {
    fprintf(stderr, ANSI_COLOR_RED "\x1b[31m"
                                   "fork failed" ANSI_COLOR_RESET);
  } else if (pid == 0) {
    execve(file_path, args, NULL);
  } else {
    pid_t child_pid = waitpid(pid, &status, 0);
    if (child_pid == -1) {
      fprintf(stderr, ANSI_COLOR_RED "wait pid failed" ANSI_COLOR_RESET);
      exit(EXIT_FAILURE);
    }
    if (!WIFEXITED(status)) {
      int exit_status = WEXITSTATUS(status);
      fprintf(stderr,
              ANSI_COLOR_RED
              "Child process %d exited with status  %d\n" ANSI_COLOR_RESET,
              child_pid, exit_status);
    } else if (WIFSIGNALED(status)) {
      int signal_num = WTERMSIG(status);
      fprintf(stderr,
              ANSI_COLOR_RED
              "child process %d exited with signal %d\n" ANSI_COLOR_RESET,
              child_pid, signal_num);
    } else if (WIFSTOPPED(status)) {
      int stop_signal = WSTOPSIG(status);
      fprintf(stderr,
              ANSI_COLOR_RED
              "Child process %d stopped by signal %d\n" ANSI_COLOR_RESET,
              child_pid, stop_signal);
    }
  }
  return status;
}
int builtin(char *command) { return 0; }
