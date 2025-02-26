#include "../headers/sh_std.h"
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
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
const char *uname() {
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw) {
    return pw->pw_name;
  }
  return "";
}
char *fpath(char *command) {
  int i = 0;
  char slash = '/';
  char **envs;
  char *cpy_penv, *file_path, *slashptr;
  const char *path_name = "PATH";
  char *penv = getenv(path_name);

  slashptr = strchr(command, slash);
  if (slashptr != NULL)
    return command;

  file_path = malloc(sizeof(char) * 1024);
  cpy_penv = malloc(sizeof(char) * strlen(penv) * 2);

  snprintf(cpy_penv, strlen(penv) + 1, "%s", penv);
  envs = split(cpy_penv, ':');
  if (!file_path) {
    fprintf(stderr, "minish: allocator error");
    exit(1);
  }
  file_path[0] = '\0';

  while (envs[i++]) {
    snprintf(file_path, 1024, "%s/%s", envs[i], command);
    if (access(file_path, F_OK | X_OK) == 0) {
      return file_path;
    }
  }
  free(envs);
  free(penv);
  return NULL;
}
