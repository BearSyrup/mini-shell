#include "../headers/sh_std.h"

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
