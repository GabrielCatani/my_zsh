#include "../includes/AST_Lexer.h"

struct AST_Lexer new () {
  return (struct AST_Lexer) {
    .root = NULL,
  };
}

const struct AST_LexerClass AST_Lexer = {
  .new = &new,
};
