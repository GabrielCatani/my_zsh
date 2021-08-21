#include "my_zsh.h"

int main(int ac, char **av, char **env)
{
  char *line = NULL;
  size_t line_cap = 0;
  size_t line_len = 0;
  struct AST_Lexer ast = AST_Lexer.new();
  char **shell_env = NULL;

  if (ac > 1) {
    printf("%d %s\n", ac, av[0]);
  }
  copy_env(env, &shell_env);
  while (1) {
    print_str(SHELL_NAME);
    print_str(PROMPT);
    while ((line_len = getline(&line, &line_cap, stdin))) {
      ast.build_AST_Lexer(&ast, line, shell_env);
      //ast.print_lexer(&ast);

      ast.CheckAndExecute(&ast, &shell_env);
      print_str(SHELL_NAME);
      print_str(PROMPT);
      ast.clearAST_Lexer(&ast);
    }
  }
  clear_array(&shell_env);
  del_array(&shell_env);
  return 0;
}
