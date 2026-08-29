#include "../include/shell.h"

char **parse_line(char *line) {
  int bufsize = MAX_ARGS;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "Allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n");
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += MAX_ARGS;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n");
  }

  tokens[position] = NULL;
  return tokens;
}
