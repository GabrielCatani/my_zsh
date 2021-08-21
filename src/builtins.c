#include "builtins.h"
#include "input_handling.h"
#include "env_handling.h"

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

int execute_builtin(int func_index, struct AST_Lexer *this, char ***env) {
  switch(func_index) {
  case 0:
    exit_builtin();
    return 1;
  case 1:
    env_builtin((*env));
    return 1;
  case 2:
    unsetenv_builtin(this, env);
    return 1;
  case 3:
    setenv_builtin(this, env);
    return 1;
  case 4:
    cd_builtin(this, (*env));
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
  if (this->root->left && this->root->left->content[1] == 'n') {
    write(1, "\033[30;47m%", 11);
    write(1, "\033[0m", 5);
  }
  write(1, "\n", 1);
}

//env()
void env_builtin(char **env) {
  if (env) {
    for (int i = 0; env[i]; i++) {
      print_str(env[i]);
      print_str("\n");
    }
  }
}
//unsetenv()
void unsetenv_builtin(struct AST_Lexer *this, char ***env) {
  
  if (this->root->right && this->root->right->content) {
    rm_from_env_list(this->root->right->content, env);
 }
}


//setenv()
void setenv_builtin(struct AST_Lexer *this, char ***env) {
  
  if (this->root->right && this->root->right->content &&
      this->root->right->right && this->root->right->right->content)   {
    add_to_env_list(this->root->right->content, this->root->right->right->content, env);
 }
}

//cd
void cd_builtin(struct AST_Lexer *this, char **env) {
  ASTNode *ptr = this->root;
  char *var_value = NULL;
  char *tmp = NULL;

  if (!ptr->right && !ptr->left) {
    var_value = get_env_var_content("HOME", env);
  }
  else if (ptr->right && ptr->right->content) {
    if (!my_strcmp(ptr->right->content, "~")) {
      var_value = get_env_var_content("HOME", env);
    }
    else if (*ptr->right->content == '~') {
      tmp = get_env_var_content("HOME", env);
      var_value = my_strjoin(tmp, &ptr->right->content[1]);
      free(tmp);
    }
    else {
      var_value = my_strdup(ptr->right->content);
    }
  }
  else if (ptr->left && ptr->left->content) {
    if (!my_strcmp(ptr->left->content, "-")) {
      var_value = get_env_var_content("OLDPWD", env);
    }
  }
  chdir(var_value);
  free(var_value);
  var_value = NULL;
}
