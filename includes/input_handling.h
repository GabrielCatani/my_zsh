#ifndef __INPUT_HANDLING_C__
#define __INPUT_HANDLING_C__
#include "my_strings.h"
char *get_next_word(char **input);
char *get_env_var_content(char *env_var, char **env);
void add_to_env_list(char *name, char *value, char ***env);
void copy_env(char **src, char ***dst);
char *get_env_var(char *env_var, char **env);
void update_var_env(char *name, char *value, char ***env);
#endif
