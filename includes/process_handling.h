#ifndef __PROCESS_HANDLING_H__
#define __PROCESS_HANDLING_H__
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "AST_Lexer.h"
int execute_binaries(char *full_path_bin, char **args, char **env);
#endif
