#include "../headers/command_list.h"
#include <stdlib.h>
#include <sys/types.h>

command_list *new_command(char *command, list_op next_op) {
  command_list *list = (command_list *)malloc(sizeof(command_list *));
  list->command = (char *)malloc(strlen(command));
  strcpy(list->command, command);
  list->next_op = next_op;
  list->next = NULL;
  return list;
}

command_list *split_command_list(char *command_literal) {
  command_list *commands;
  char **args;

  if (strstr(command_literal, "&&") != NULL) {
    args = split(command_literal, "&&");
    commands = new_command(args[0], AND_OP);
  } else if (strstr(command_literal, "||")) {
    args = split(command_literal, "||");
    commands = new_command(args[0], OR_OP);
  } else {
    commands = new_command(command_literal, NO_OP);
    return commands;
  }

  while (1) {
    commands->next = new_command(args[1], NO_OP);
    break;
  }
  return commands;
}
