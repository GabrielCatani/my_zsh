#ifndef __AST_LEXER_H__
#define __AST_LEXER_H__
#include <stdio.h>
#include <stdlib.h>

typedef struct ASTNode {
  struct ASTNode *left;
  struct ASTNode *right;
  char *content;
} ASTNode;

struct AST_Lexer {
  ASTNode *root;
  
  void (* const print)(struct AST_Lexer *this);
  void (*const insert)(struct AST_Lexer *this, char *content);
  void (*const destroy)(struct AST_Lexer **this);
  char (*const getFullCommand)(struct AST_Lexer *this);
};

extern const struct AST_LexerClass {
  struct AST_Lexer (*new)();
} AST_Lexer;
#endif
