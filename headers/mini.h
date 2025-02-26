#ifndef MINI
#define MINI
#include "../headers/directory.h"
#include "../headers/sh_std.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFSIZE 2048

char *sh_readline();
int sh_exec(char *command);
#endif // !MINI
