#include "../headers/mini.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  char **args;
  char *file_path;

  args = split(command, ' ');

  int pid;
  if (strcmp(command, "cd") != 0) {

    file_path = fpath(command);
    // execvp(args[0], args);
    pid = fork();
    if (pid == 0) {
      execve(file_path, args, NULL);
      free(file_path);
    }
    wait(&pid);
    return;
  }

  go_directory(args[1]);
}
