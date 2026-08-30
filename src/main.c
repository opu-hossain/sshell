#include "../include/shell.h"

int main(void) {
  char *line;
  command_t *cmd;
  int running = 1;

  while (running) {
    printf("sshell> ");
    fflush(stdout);

    line = read_line();
    if (line == NULL) {
      printf("\n");
      break;
    }

    cmd = parse_line(line);

    if (cmd->argv[0] != NULL) {
      running = execute(cmd);
    }

    free(line);
    free_command(cmd);
  }

  return 0;
}
