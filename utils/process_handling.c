#include "process_handling.h"
#include "my_zsh.h"

int execute_binaries(char *full_path_bin, char **args, char **env) {

  pid_t pid;

  printf("%s %s %s\n", full_path_bin, args[0], env[0]);
  pid = fork();
  if (pid > 0) {
      printf("Parent %d\n", getpid());
  }
  else {
      printf("Child %d\n", getpid());
  }
  return 1;
}
