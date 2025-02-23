#include "../headers/directory.h"

int go_directory(char *directory) {
  if (!directory)
    chdir("~");

  char *full_path;
  full_path = malloc(PATH_MAX);
  get_real_path(directory, &full_path);

  if (chdir(full_path) != 0) {
    perror(directory);
    return 0;
  }
  return 1;
}
void get_working_dir(char **buff) {
  char path[PATH_MAX];
  if (!getcwd(path, PATH_MAX)) {
    perror("error: ");
  }
  strcpy(*buff, path);
}
void get_real_path(const char *directory, char **buff) {
  char *path;
  path = malloc(PATH_MAX);
  get_working_dir(&path);
  strcpy(*buff, strcpy(path, directory));
  free(path);
}
