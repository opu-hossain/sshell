#include "../include/shell.h"

char *read_line(void) {
  char *line = NULL;
  size_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      free(line);
      return NULL;
    } else {
      perror("redline");
      free(line);
      exit(EXIT_FAILURE);
    }
  }

  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }

  return line;
}
