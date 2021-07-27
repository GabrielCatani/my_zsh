#include "my_zsh.h"
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
      ast.build_AST_Lexer(&ast, line);
      ast.print_lexer(&ast);

      ast.CheckAndExecute(&ast);
      write(1, PROMPT, PROMPT_LEN);
      ast.clearAST_Lexer(&ast);
    }
  }
  return 0;
}
