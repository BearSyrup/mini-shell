#include "../headers/main.h"

int main(void) {
  char *line;
  char hostname[1024];
  gethostname(hostname, 1024);

  while (1) {
    printf(ANSI_COLOR_BLUE "[%s@%s]" ANSI_COLOR_RESET ANSI_COLOR_CYAN
                           " >> " ANSI_COLOR_RESET,
           uname(), hostname);
    line = sh_readline();
    sh_exec(line);
  }
  return EXIT_SUCCESS;
}
