#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define EXIT_SUCCESS 0

char **sh_readline() {
  char **args;
  char *tofree, *buffer, *token, *str;

  int position;
  size_t n;
  n = 0;
  getline(&buffer, &n, stdin);
  tofree = str = strdup(buffer);
  position = 1;
  args = malloc(strlen(buffer) * (sizeof(char) + 1));

  token = strtok(str, " ");
  args[0] = malloc(strlen(token) * sizeof(char));
  strcpy(args[0], token);

  while ((token = strtok(NULL, " "))) {
    args[position] = malloc(strlen(token) * sizeof(char));
    strcpy(args[position], token);
    position++;
  }
  args[++position] = malloc(sizeof(char));
  args[position] = NULL;
  return args;
}
void sh_exec(char *command, char **args) {
  int pid;
  pid = fork();
  if (pid == 0) {
    execvp(command, args);
  }
  wait(&pid);
}

int main(void) {
  char **args;
  while (1) {
    printf("$ ");
    args = sh_readline();
    sh_exec(args[0], args);
  }
  return EXIT_SUCCESS;
}
