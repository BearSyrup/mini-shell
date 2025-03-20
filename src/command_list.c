#include "../headers/command_list.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

command_list *new_command(char *command, list_op next_op) {
  command_list *list = (command_list *)malloc(sizeof(command_list *));
  list->command = (char *)malloc(strlen(command));
  strcpy(list->command, command);
  list->next_op = next_op;
  list->next = NULL;
  list->tail = NULL;
  return list;
}

void add_command(command_list *list, char *command, list_op next_op) {
  if (list->tail != NULL) {
    command_list *current = list->tail;
    current->next = new_command(command, next_op);
    list->tail = current->next;
  } else {
    list->next = new_command(command, next_op);
    list->tail = list->next;
  }
}

void command_clean(command_list *list) {
  command_list *tmp;
  while (list != NULL) {
    tmp = list;
    list = list->next;
    free(tmp);
  }
}

command_list *split_command_list(char *command_literal) {
  command_list *commands;
  list_op op;
  char *operator;
  char **args;

  operator= get_first_op(command_literal);
  if (operator== NULL) {
    commands = new_command(command_literal, NO_OP);
    return commands;
  }
  args = split_first(command_literal, operator);
  op = get_op(operator);
  commands = new_command(args[0], op);

  while (1) {
    operator= get_first_op(args[1]);
    if (operator== NULL) {
      add_command(commands, args[1], NO_OP);
      return commands;
    }
    args = split_first(args[1], operator);
    op = get_op(operator);
    add_command(commands, args[0], op);
  }

  return commands;
}

list_op get_op(char *op) {
  if (strstr(op, "&&")) {
    return AND_OP;
  } else if (strstr(op, "||")) {
    return OR_OP;
  } else if (strstr(op, ";")) {
    return COMMA_OP;
  } else {
    return NO_OP;
  }
}

char *get_first_op(char *command_literal) {
  const char *ops[] = {"&&", "||", ";", NULL};
  char *current_ptr, *first_ptr, *operator;
  int i;

  i = 0;
  operator= NULL;
  first_ptr = NULL;
  while (ops[i]) {
    current_ptr = strstr(command_literal, ops[i]);
    if (current_ptr != NULL && first_ptr == NULL) {
      first_ptr = current_ptr;
      operator= malloc(sizeof(char *));
      strcpy(operator, ops[i]);
      continue;
    }

    if (current_ptr && (current_ptr < first_ptr)) {
      first_ptr = current_ptr;
      strcpy(operator, ops[i]);
    }
    i++;
  }
  return operator;
}
