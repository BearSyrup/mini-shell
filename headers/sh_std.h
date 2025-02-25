#ifndef SH_STD
#define SH_STD
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
char **split(char *str, const char a_delim);
char *fpath(char *command);
#endif
