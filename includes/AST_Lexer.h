#ifndef __AST_LEXER_H__
#define __AST_LEXER_H__
typedef struct ASTNode {
  struct ASTNode *left;
  struct ASTNode *right;
  char *content;
  int len_content;
} ASTNode;

struct AST_Lexer {
  ASTNode *root;
  
  void (* const print_lexer)(struct AST_Lexer *this);
  void (* const build_AST_Lexer)(struct AST_Lexer *this, char *input);
  void (* const destroy)(struct AST_Lexer *this);
  void (* const CheckAndExecute)(struct AST_Lexer *this);
  void (* const clearAST_Lexer)(struct AST_Lexer *this);
};

extern const struct AST_LexerClass {
  struct AST_Lexer (*new)();
} AST_Lexer;
#endif
