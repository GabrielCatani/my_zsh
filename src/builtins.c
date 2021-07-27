#include "builtins.h"

int is_builtin(char *command) {
  const char *builtins[] = {"exit", "env", "unsetenv", "setenv", "cd", "echo"};

  if (!command) {
    return -1;
  }

  for (int i = 0; i < 6; i++) {
    if (!strcmp(command, builtins[i])) {
      return i;
    }
  }
  return -1;
}

int execute_builtin(int func_index, struct AST_Lexer *this) {
  switch(func_index) {
  case 0:
    exit_builtin();
    return 1;
  case 5:
    echo_builtin(this);
    return 1;
  }
  return 0;
}

void exit_builtin() {
  exit(0);
}

void echo_builtin(struct AST_Lexer *this) {
  ASTNode *ptr = this->root;

  ptr = ptr->right;
  while (ptr) {
    if (ptr->content) {
      write(1, ptr->content, ptr->len_content);
    }

    ptr = ptr->right;
  }
}

//env()

//unsetenv()

//setenv()

//cd

//echo
