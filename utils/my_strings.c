#include "my_strings.h"

int my_strlen(char *str) {
  int len = 0;

  if (!str) {
    return len;
  }
  
  while (str[len]) {
    len++;
  }

  return len;
}

char *my_strndup(char *str, int len) {
  if (!str || len == 0) {
    return NULL;
  }

  char *new_str = NULL;

  new_str = (char *)malloc(sizeof(char) * len);
  if (!new_str) {
    return NULL;
  }

  for (int i = 0; i < len; i++) {
    new_str[i] = str[i];
  }

  new_str[len] = '\0';
  return new_str;
}

char *my_strdup(char *str) {
  if (!str) {
    return NULL;
  }

  char *new_str = NULL;
  int len = my_strlen(str) + 1;
  new_str = (char *)malloc(sizeof(char) * len);
  if (!new_str) {
    return NULL;
  }

  for (int i = 0; i < len; i++) {
    new_str[i] = str[i];
  }
  
  new_str[len] = '\0';
  return new_str;
}
