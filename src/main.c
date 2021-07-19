#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "AST_Lexer.h"
#define PROMPT "catanis_zsh$>"
#define PROMPT_LEN 13

int main(void)
{

  char *line = NULL;
  size_t line_cap = 0;
  size_t line_len = 0;
  struct AST_Lexer ast = AST_Lexer.new();

  while (1){
    write(1, PROMPT, PROMPT_LEN);
    while ((line_len = getline(&line, &line_cap, stdin))){
      write(1, line, line_len);
      ast.root = (ASTNode *)malloc(sizeof(ASTNode));
      ast.root->content = strdup(line);
      write(1, ast.root->content, line_len);
      write(1, PROMPT, PROMPT_LEN);      
    }
  }
  return 0;
}
