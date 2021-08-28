#ifndef __ENV_HANDLING_C__
#define __ENV_HANDLING_C__
#include "my_strings.h"
#include "input_handling.h"
void form_path(char *path, char *file, char **full_path);
void add_to_env_list(char *name, char *value, char ***env);
void copy_env(char **src, char ***dst);
void update_var_env(char *name, char *value, char ***env);
char *form_env_var(char *name, char *value);
void rm_from_env_list(char *name, char ***env);
#endif
