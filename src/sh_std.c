#include "../headers/sh_std.h"
#include <stdio.h>
#include <unistd.h>

char **split(char *str, const char a_delim) {
  char **result;
  size_t count, idx;
  char *tmp, *token;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = '\0';

  count = 0;
  tmp = strdup(str);
  while (*tmp) {
    if (*tmp == a_delim) {
      count++;
    }
    tmp++;
  }
  count++;
  result = malloc(sizeof(char *) * count);

  if (result) {
    idx = 0;
    token = strtok(str, delim);

    while (token) {
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }

    *(result + idx++) = NULL;
  }

  return result;
}
char *fpath(char *command) {
  char **envs;
  const char *path_name = "PATH";
  char *penv = getenv(path_name);
  char *file_path;
  int i = 0;

  envs = split(penv, ':');

  file_path = malloc(sizeof(char) * 1024);

  if (!file_path) {
    fprintf(stderr, "minish: allocator error");
    exit(1);
  }
  file_path[0] = '\0';

  while (envs[i++]) {
    snprintf(file_path, 1024, "%s/%s", envs[i], command);
    if (access(file_path, F_OK | X_OK) == 0) {
      free(envs);
      return file_path;
    }
  }
  free(envs);
  return NULL;
}
