#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"
#define INCLUDE_FOLDER "include/"

static const char *sources[] = {
    "main.c", "reader.c", "parser.c", "builtins.c", "executor.c",
};

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER))
    return 1;

  Nob_Cmd cmd = {0};

  nob_cmd_append(&cmd, "cc", "-I", INCLUDE_FOLDER, "-o", BUILD_FOLDER "sshell");
  for (size_t i = 0; i < NOB_ARRAY_LEN(sources); ++i) {
    nob_cmd_append(&cmd, nob_temp_sprintf("%s%s", SRC_FOLDER, sources[i]));
  }

  if (!nob_cmd_run(&cmd))
    return 1;

  return 0;
}
