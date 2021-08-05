#include "my_zsh.h"
#define PROMPT "catanis_zsh$>"

int main(int ac, char **av, char **env)
{
  char *line = NULL;
  size_t line_cap = 0;
  size_t line_len = 0;
  struct AST_Lexer ast = AST_Lexer.new();
  char **shell_env = copy_env(env);

  printf("%d %s\n", ac, av[0]);
  while (1) {
    print_str(PROMPT);
    while ((line_len = getline(&line, &line_cap, stdin))) {
      ast.build_AST_Lexer(&ast, line);
      //      ast.print_lexer(&ast);

      ast.CheckAndExecute(&ast, &shell_env);
      print_str(PROMPT);
      ast.clearAST_Lexer(&ast);
    }
  }

  free(shell_env);
  shell_env = NULL;
  return 0;
}
