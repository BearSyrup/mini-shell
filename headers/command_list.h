#ifndef COMMAND_LIST
#define COMMAND_LIST

#include "sh_std.h"
#include <stdlib.h>
#include <string.h>
typedef enum { AND_OP, OR_OP, COMMA_OP, NO_OP } list_op;

typedef struct node {
  char *command;
  list_op next_op;
  struct node *next;
} command_list;

command_list *new_command(char *command, list_op next_op);
command_list *split_command_list(char *command_literal);
#endif
