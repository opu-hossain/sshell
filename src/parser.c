#include "../include/shell.h"

command_t *parse_line(char *line) {
  command_t *cmd = malloc(sizeof(command_t));
  if (cmd == NULL) {
    perror("malloc");
    exit(1);
  }

  cmd->argv = malloc(MAX_ARGS * sizeof(char *));
  if (cmd->argv == NULL) {
    perror("malloc");
    exit(1);
  }

  cmd->input_file = NULL;
  cmd->output_file = NULL;
  cmd->append = 0;

  int argc = 0;
  char *token = strtok(line, " \t");

  while (token != NULL && argc < MAX_ARGS - 1) {
    if (strcmp(token, "<") == 0) {
      token = strtok(NULL, " \t");
      cmd->input_file = token;
    } else if (strcmp(token, ">>") == 0) {
      token = strtok(NULL, " \t");
      cmd->output_file = token;
      cmd->append = 1;
    } else if (strcmp(token, ">") == 0) {
      token = strtok(NULL, " \t");
      cmd->output_file = token;
      cmd->append = 0;
    } else {
      cmd->argv[argc] = token;
      argc++;
    }

    token = strtok(NULL, " \t");
  }

  cmd->argv[argc] = NULL;

  return cmd;
}

void free_command(command_t *cmd) {
  free(cmd->argv);
  free(cmd);
}
