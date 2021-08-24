#include "AST_Lexer.h"
#include "builtins.h"
#include "input_handling.h"
#include "process_handling.h"
#include "env_handling.h"
#include "my_zsh.h"

void print_preorder(ASTNode *root) {
  if (!root) {
    return;
  }

  write(1, root->content, root->len_content);
  write(1, "\n", 1);

  print_preorder(root->left);
  print_preorder(root->right);
}

static void print_lexer(struct AST_Lexer *this) {
  if (this && this->root) {
    print_preorder(this->root);
  }
}

static void build_AST_Lexer(struct AST_Lexer *this, char *input, char **env) {
  if (!input || *input == '\n') {
    return;
  }
  this->root = (ASTNode *)malloc(sizeof(ASTNode));
  if (!this->root) {
    return;
  }

  this->root->content = get_next_word(&input);
  this->root->len_content = my_strlen(this->root->content);
  this->root->right = NULL;
  this->root->left = NULL;

  char *tmp = NULL;

  ASTNode **ptr = &(this->root);
  while ((tmp = get_next_word(&input))) {
    if (tmp[0] == '~') {
      convert_home(&tmp, env);
    }
    ptr = &(this->root);
    if (*tmp == '-') {
      while ((*ptr)) {
        ptr = &(*ptr)->left;
      }
      (*ptr) = (ASTNode *)malloc(sizeof(ASTNode));
      (*ptr)->content = my_strdup(tmp);
      (*ptr)->len_content = my_strlen(tmp);
      (*ptr)->right = NULL;
      (*ptr)->left = NULL;      
    }
    else {
      while ((*ptr)) {
        ptr = &(*ptr)->right;
      }
      (*ptr) = (ASTNode *)malloc(sizeof(ASTNode));
      (*ptr)->content = my_strdup(tmp);
      (*ptr)->len_content = my_strlen(tmp);
      (*ptr)->right = NULL;
      (*ptr)->left = NULL;
    }
    free(tmp);
  }
}

static void CheckAndExecute(struct AST_Lexer *this, char ***env) {
  char **bin_paths = NULL;
  char *full_path_bin = NULL;
  char **args = NULL;
  char *PATH_content = NULL;
  char valid_command = 0;
  
  if (this->root && execute_builtin(is_builtin(this->root->content), this, env)) {
    valid_command = 1;
  }
  else if (this->root) {
    PATH_content = get_env_var_content("PATH", (*env));
    my_strtrim(PATH_content, ':', &bin_paths);
    form_args(this, &args);
    for (int i = 0; bin_paths[i]; i++) {
      form_path(bin_paths[i], this->root->content, &full_path_bin);
      if (is_in_dir(bin_paths[i], this->root->content)) {
	execute_binaries(full_path_bin, args, (*env));
	valid_command = 1;
      }
      free(full_path_bin);
      full_path_bin = NULL;
    }
    for (int j = 0; args[j]; j++) {
      free(args[j]);
    }
    free(args);
    free(PATH_content);
    del_array(&bin_paths);
  }
  if (this->root && !valid_command) {
    print_str(SHELL_NAME);
    print_str(": command not found: ");
    print_str(this->root->content);
    print_str("\n");
  }
}

static void clearAST_Lexer(struct AST_Lexer *this) {
  ASTNode *ptr = NULL;
  ASTNode *tmp = NULL;

  ptr = this->root->right;
  while (ptr) {
    tmp = ptr->right;
    free(ptr->content);
    free(ptr);
    ptr = tmp;
  }

 ptr = this->root->left;
  while (ptr) {
    tmp = ptr->left;
    free(ptr->content);
    free(ptr);
    ptr = tmp;
  }
  free(this->root->content);
  free(this->root);
}

struct AST_Lexer new () {
  return (struct AST_Lexer) {
    .root = NULL,
    .print_lexer = &print_lexer,
    .build_AST_Lexer = &build_AST_Lexer,
    .CheckAndExecute = &CheckAndExecute,
    .clearAST_Lexer = &clearAST_Lexer,
  };
}

const struct AST_LexerClass AST_Lexer = {
  .new = &new,
};
