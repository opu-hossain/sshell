#ifndef SHELL_H_
#define SHELL_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_PATH 256

void shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
int execute_builtin(char **args);
int launch_process(char **args);
void handle_signlas(int sig);

#endif
