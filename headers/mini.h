#ifndef MINI
#define MINI
#include "colors.h"
#include "directory.h"
#include "sh_std.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFSIZE 2048

char *sh_readline();
void sh_exec(char *command);
int command_exec(char *file_path, char **args);
#endif // !MINI
