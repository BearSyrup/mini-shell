#ifndef SH_STD
#define SH_STD
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
char **split(char *str, const char *delim);
char *fpath(char *command);
const char *uname();
char **split_first(char *str, const char *delim);
#endif
