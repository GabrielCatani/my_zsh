#ifndef __BUILTINS_H__
#define __BUILTINS_H__
#include "my_strings.h"
#include <strings.h>
#include "AST_Lexer.h"
#include <unistd.h>
int is_builtin(char *command);
int execute_builtin(int func_index, struct AST_Lexer *this, char ***env);
//Builtin Functions
void exit_builtin();
void echo_builtin(struct AST_Lexer *this);
void cd_builtin(struct AST_Lexer *this, char **env);
void env_builtin(char **env);
void setenv_builtin(struct AST_Lexer *this, char ***env);
void unsetenv_builtin(struct AST_Lexer *this, char ***env);
#endif
