#include "input_handling.h"

char *get_next_word(char **input) {
  char *word = NULL;
  int end = 0;

  while (*(*input) == 32 && *(*input) != '\0') {
    (*input)++;
  }
  
  while ((*input)[end] != 32 &&
	 (*input)[end] != '\0' &&
	 (*input)[end] != '\n') {
    end++;
  }

  
  word = my_strndup(*input, end);
  (*input) += end;

  return word;
}
