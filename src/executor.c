#include "../include/shell.h"

static int run_external(char **args) {

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      fprintf(stderr, "%s: command not found\n", args[0]);
      exit(1);
    }
  }

  int status;
  waitpid(pid, &status, 0);

  return 1;
}

int execute(char **args) {
  int should_continue;

  if (run_builtin(args, &should_continue)) {
    return should_continue;
  }

  return run_external(args);
}
