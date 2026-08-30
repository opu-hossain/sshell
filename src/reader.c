#include "../include/shell.h"

char *read_line(void) {
  char *line = NULL;
  size_t size = 0;

  ssize_t chars_read = getline(&line, &size, stdin);

  if (chars_read == -1) {
    free(line);
    return NULL;
  }

  if (line[chars_read - 1] == '\n') {
    line[chars_read - 1] = '\0';
  }

  return line;
}
