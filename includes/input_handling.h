#ifndef __INPUT_HANDLING_C__
#define __INPUT_HANDLING_C__
#include "my_strings.h"
#include <dirent.h>
#include "AST_Lexer.h"
void form_args(struct AST_Lexer *ast, char ***args);
int count_nodes (struct AST_Lexer *ast);
int is_in_dir(char *file_name, char *dir_name);
char *get_next_word(char **input);
char *get_env_var_content(char *env_var, char **env);
char *get_env_var(char *env_var, char **env);
void get_bin_src_from_path(char *PATH, char ***bin_paths);
void convert_home(char **input, char **env);
#endif
