#include "../include/shell.h"

char **parse_line(char *line) {
  char **args = malloc(MAX_ARGS * sizeof(char *));
  if (args == NULL) {
    perror("malloc");
    exit(1);
  }

  int count = 0;
  char *token = strtok(line, " \t");

  while (token != NULL && count < MAX_ARGS - 1) {
    args[count++] = token;
    token = strtok(NULL, " \t");
  }
  args[count] = NULL;

  return args;
}
