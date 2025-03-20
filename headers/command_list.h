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
  struct node *tail;
} command_list;

command_list *new_command(char *command, list_op next_op);
void add_command(command_list *list, char *command, list_op next_op);
void command_clean(command_list *list);
command_list *split_command_list(char *command_literal);
char *get_first_op(char *command_literal);
list_op get_op(char *op);
#endif
