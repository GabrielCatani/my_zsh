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

int my_strlen_sep(char *str, char sep) {
  int len = 0;
  while (str[len] != sep && str[len] != '\0') {
    len++;
  }

  return len;
}

void my_strtrim(char *str, char sep, char ***trimed) {
  int index = 0;
  int sep_nbr = 0;

  while (str[index]) {
    if (str[index] == sep) {
      sep_nbr++;
    }
    index++;
  }

  sep_nbr++;
  int str_len = 0;
  (*trimed) = (char **)malloc(sizeof(char *) * sep_nbr);
  str_len = my_strlen_sep(str, sep);
  (*trimed)[0] = (char *)malloc(sizeof(char) * (str_len + 1));
  for (int i = 0; i < str_len; i++) {
    (*trimed)[0][i] = str[i];
  }

  int bunda = str_len;
  str_len = my_strlen_sep(&str[++str_len], sep);
  (*trimed)[1] = (char *)malloc(sizeof(char) * (str_len + 1));
  for (int i = 0; i < str_len; i++) {
    (*trimed)[1][i] = str[bunda];
    bunda++;
  }
}

int my_strcmp(char *s1, char *s2) {

  int index = 0;

  while (s1[index] && s2[index] && s1[index] == s2[index]) {
    index++;
  }

  return (s1[index] - s2[index]);
}

char *my_strjoin(char *s1, char *s2) {
  char *new_str = NULL;
  int len = 0;

  if (!s1 || !s2) {
    return NULL;
  }

  len = my_strlen(s1);
  len += my_strlen(s2) + 1;

  new_str = (char *)malloc(sizeof(char) * len);
  if (!new_str) {
    return NULL;
  }

  int index = 0;
  while (s1[index]) {
    new_str[index] = s1[index];
    index++;
  }

  int i = 0;
  while (s2[i]) {
    new_str[index] = s2[i];
    index++;
    i++;
  }

  new_str[index] = '\0';
  return new_str;
}

void print_str(char *str) {
  write(1, str, my_strlen(str));
}
