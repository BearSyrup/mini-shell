#include "../headers/main.h"

int main(void) {
  char *line;

  while (1) {
    printf("$ ");
    line = sh_readline();
    sh_exec(line);
  }
  return EXIT_SUCCESS;
}
