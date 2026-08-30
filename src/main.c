#include "../include/shell.h"

int main(void) {
  char *line;
  char **args;
  int running = 1;

  while (running) {
    printf("sshell> ");
    fflush(stdout);

    line = read_line();
    if (line == NULL) {
      printf("\n");
      break;
    }

    args = parse_line(line);

    if (args[0] != NULL) {
      running = execute(args);
    }

    free(line);
    free(args);
  }

  return 0;
}
