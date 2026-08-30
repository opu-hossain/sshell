#include "../include/shell.h"

int builtin_cd(char **args) {
  char *target_dir;

  if (args[1] == NULL) {
    target_dir = getenv("HOME");
    if (target_dir == NULL) {
      fprintf(stderr, "cd: HOME is no set\n");
      return 1;
    }
  } else {
    target_dir = args[1];
  }

  if (chdir(target_dir) != 0) {
    perror("cd");
  }

  return 1;
}

int builtin_help(char **args) {
  (void)args;

  printf("Built-in commands:\n");
  printf("  cd <dir>   change the current directory\n");
  printf("  exit       quit the shell\n");
  printf("  help       show this message\n");

  return 1;
}

int builtin_exit(char **args) {
  (void)args;
  return 0;
}

int run_builtin(char **args, int *should_continue) {
  if (strcmp(args[0], "cd") == 0) {
    *should_continue = builtin_cd(args);
    return 1;
  }
  if (strcmp(args[0], "exit") == 0) {
    *should_continue = builtin_exit(args);
    return 1;
  }
  if (strcmp(args[0], "help") == 0) {
    *should_continue = builtin_help(args);
    return 1;
  }

  return 0;
}
