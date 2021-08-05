#include "AST_Lexer.h"
#include "builtins.h"
#include "input_handling.h"

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

static void build_AST_Lexer(struct AST_Lexer *this, char *input) {
  if (!input || *input == '\n') {
    return;
  }
  this->root = (ASTNode *)malloc(sizeof(ASTNode));
  if (!this->root) {
    return;
  }

  this->root->content = get_next_word(&input);
  this->root->len_content = my_strlen(this->root->content);

  char *tmp = NULL;

  ASTNode **ptr = &(this->root);
  while ((tmp = get_next_word(&input))) {
    ptr = &(this->root);
    if (*tmp == '-') {
      while ((*ptr)) {
        ptr = &(*ptr)->left;
      }
      (*ptr) = (ASTNode *)malloc(sizeof(ASTNode));
      (*ptr)->content = my_strdup(tmp);
      (*ptr)->len_content = my_strlen(tmp);
    }
    else {
      while ((*ptr)) {
        ptr = &(*ptr)->right;
      }
      (*ptr) = (ASTNode *)malloc(sizeof(ASTNode));
      (*ptr)->content = my_strdup(tmp);
      (*ptr)->len_content = my_strlen(tmp);
    }
    free(tmp);
  }
}

static void CheckAndExecute(struct AST_Lexer *this, char ***env) {

  if (this->root && execute_builtin(is_builtin(this->root->content), this, env)) {
    //    printf("Executing...%s\n", this->root->content);
  }
  else {
    printf("Command not found\n");
  }
}

static void clearAST_Lexer(struct AST_Lexer *this) {
  ASTNode **ptr = &(this->root);
  ASTNode **tmp = ptr;

  if (!this->root) {
    return;
  }

  ptr = &(this->root->right);
  while ((*ptr)) {
    tmp = ptr;
    ptr = &(*ptr)->right;
    free((*tmp)->content);
    free((*tmp));
  }
  ptr = &(this->root->left);
  tmp = ptr;

  while ((*ptr)) {
    tmp = ptr;
    ptr = &(*ptr)->left;
    free((*tmp)->content);
    free((*tmp));
  }

  free(this->root->content);
  this->root->content = NULL;
  free(this->root);
  this->root = NULL;
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
