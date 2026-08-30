#include "../include/shell.h"
#include <fcntl.h>

static void apply_redirection(command_t *cmd) {
  if (cmd->input_file != NULL) {
    int fd = open(cmd->input_file, O_RDONLY);
    if (fd == -1) {
      perror(cmd->input_file);
      exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
  }

  if (cmd->output_file != NULL) {
    int flags = O_WRONLY | O_CREAT;
    flags |= cmd->append ? O_APPEND : O_TRUNC;

    int fd = open(cmd->output_file, flags, 0644);
    if (fd == -1) {
      perror(cmd->input_file);
      exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
  }
}

static int run_external(command_t *cmd) {

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    apply_redirection(cmd);

    if (execvp(cmd->argv[0], cmd->argv) == -1) {
      fprintf(stderr, "%s: command not found\n", cmd->argv[0]);
      exit(1);
    }
  }

  int status;
  waitpid(pid, &status, 0);

  return 1;
}

int execute(command_t *cmd) {
  int should_continue;

  if (run_builtin(cmd->argv, &should_continue)) {
    return should_continue;
  }

  return run_external(cmd);
}
