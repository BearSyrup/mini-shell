#include "../headers/main.h"
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  char *line;
  pid_t result;
  char hostname[1024];
  gethostname(hostname, 1024);

  while (1) {
    printf(ANSI_COLOR_BLUE "[%s@%s]" ANSI_COLOR_RESET ANSI_COLOR_CYAN
                           " >> " ANSI_COLOR_RESET,
           uname(), hostname);
    line = sh_readline();
    result = sh_exec(line);
  }
  return EXIT_SUCCESS;
}
