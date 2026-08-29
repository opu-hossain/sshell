#include "../include/shell.h"

int execute_command(char **args) {
  if (execute_builtin(args)) {
    return 1;
  }

  return launch_process(args);
}

int launch_process(char **args) {
  pid_t pid, wpid;
  int status;

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      char path[MAX_PATH];
      snprintf(path, sizeof(path), "/bin/%s", args[0]);
      execv(path, args);

      snprintf(path, sizeof(path), "/usr/bin/%s", args[0]);
      execv(path, args);

      fprintf(stderr, "%s: command not found\n", args[0]);
      exit(EXIT_FAILURE);
    }
  } else if (pid < 0) {
    perror("fork");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}
