#include "process_handling.h"
#include "my_zsh.h"

int execute_binaries(char *full_path_bin, char **args, char **env) {

  pid_t pid;
  pid_t wpid;
  int status;
  
  pid = fork();

  if (pid == 0) {
    if (execve(full_path_bin, args, env) == -1) {
      perror(PROMPT);
    }

    exit(EXIT_FAILURE);
  }
  else {
    while ((wpid = waitpid(pid, &status, WUNTRACED))) {
      if (WIFEXITED(status) || WIFSIGNALED(status)) {
        break;
      }
    }
  }

  return 1;
}
