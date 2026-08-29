#include "../include/shell.h"

int main(int argc, char **argv) {
  signal(SIGINT, handle_signlas);
  signal(SIGCHLD, SIG_IGN);

  shell_loop();

  return 0;
}

void shell_loop(void) {
  char *line;
  char **args;
  int status = 1;

  do {
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("%s> ", cwd);
    } else {
      printf("> ");
    }

    line = read_line();
    if (line == NULL)
      break;

    args = parse_line(line);

    if (args[0] != NULL) {
      status = execute_command(args);
    }

    free(line);
    free(args);
  } while (status);
}

void handle_signlas(int sig) {
  if (sig == SIGINT) {
    printf("\n");
    char cwd[MAX_PATH];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("%s> ", cwd);
    }
    fflush(stdout);
  }
}
