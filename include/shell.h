#ifndef SHELL_H_
#define SHELL_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 64

typedef struct {
  char **argv;
  char *input_file;
  char *output_file;
  int append;
} command_t;

char *read_line(void);
command_t *parse_line(char *line);
void free_command(command_t *cmd);

int run_builtin(char **args, int *should_continue);

int builtin_cd(char **args);
int builtin_exit(char **args);
int builtin_help(char **args);

int execute(command_t *cmd);

#endif
