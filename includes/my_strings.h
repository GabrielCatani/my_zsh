#ifndef __MY_STRINGS_H__
#define __MY_STRINGS_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int my_strlen(char *str);
char *my_strndup(char *str, int len);
char *my_strdup(char *str);
char **my_strtrim(char *str, char sep);
int my_strcmp(char *s1, char *s2);
char *my_strjoin(char *s1, char *s2);
void print_str(char *str);
#endif
