#ifndef DIRECTORY
#define DIRECTORY
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void get_real_path(const char *directory, char **buff);
void get_working_dir(char **buff);
int go_directory(char *direrctory);
#endif // !DIRECTORY
