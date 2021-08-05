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

char **my_strtrim(char *str, char sep) {
  char **trimed = NULL;
  int index = 0;
  int sep_nbr = 0;
  int start = 0;
  int end = 0;

  while (str[index]) {
    if (str[index] == sep) {
      sep_nbr++;
    }
    index++;
  }

  sep_nbr++;
  trimed = (char **)malloc(sizeof(char *) * sep_nbr);

  int i = 0;
  while (str[end]) {
    if (str[end] == sep) {
      trimed[i] = my_strndup(&str[start], end - start);
      i++;
      start = end + 1;
    }
    end++;
  }
  trimed[i] = my_strndup(&str[start], end - start);

  return trimed;
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
