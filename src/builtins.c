#include "../include/shell.h"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);
int shell_pwd(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "pwd",
};

int (*builtin_func[])(char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit,
    &shell_pwd,
};

int num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

int execute_builtin(char **args) {
  for (int i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return 0;
}

int shell_cd(char **args) {
  if (args[1] == NULL) {
    char *home = getenv("HOME");

    if (home) {
      chdir(home);
    } else {
      fprintf(stderr, "cd: HOME not set\n");
    }
  } else if (strcmp(args[1], "~") == 0) {
    char *home = getenv("HOME");
    if (home) {
      chdir(home);
    }
  } else {
    if (chdir(args[1]) != 0) {
      perror("cd");
    }
  }
  return 1;
}

int shell_help(char **args) {
  printf("Simple Shell\n");
  printf("Buit-in commands: \n");
  for (int i = 0; i < num_builtins(); i++) {
    printf(" %s\n", builtin_str[i]);
  }
  printf("Use man commands for external commands. \n");
  return 1;
}

int shell_exit(char **args) {
  exit(1);
  return 0;
}

int shell_pwd(char **args) {
  char cwd[MAX_PATH];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    perror("pwd");
  }

  return 1;
}
