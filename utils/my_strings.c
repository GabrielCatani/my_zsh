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

  new_str = (char *)malloc(sizeof(char) * (len + 1));

  for (int i = 0; i < len; i++) {
    new_str[i] = str[i];
  }

  new_str[len] = '\0';
  return new_str;
}

char *my_strdup(char *str) {
  char *new_str = NULL;
  int len = my_strlen(str);

  if (!str) {
      return NULL;
  }

  new_str = (char *)malloc(sizeof(char) * (len + 1));
  if (!str) {
      return NULL;
  }
  int i = 0;
  while (str[i] != '\0') { 
    new_str[i] = str[i];
    i++;
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
  int chuncks = 0;
  
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == sep) {
      chuncks++;
    }
  }
  chuncks++;

  (*trimed) = (char **)malloc(sizeof(char *) * (chuncks + 1));
  int str_len = 0;
  for (int i = 0; i < chuncks; i++) {
    str_len = my_strlen_sep(str, sep);
    (*trimed)[i] = my_strndup(str, str_len);
    str += str_len + 1;
  }
  (*trimed)[chuncks] = NULL;
}

int my_strcmp(char *s1, char *s2) {

  int index = 0;

  while (s1[index] && s2[index] && s1[index] == s2[index]) {
    index++;
  }

  return (s1[index] - s2[index]);
}

char *my_strjoin(char *s1, char *s2) {
  char *str;
  int i;

  if(!s1 || !s2) {
    return(NULL);
  }

  str = (char*)malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
  if(!str) {
    return (NULL);
  }

  i = 0;
  while(*s1 != '\0') {
    str[i++] = *s1++;
  }

  while(*s2 != '\0') {
    str[i++] = *s2++;
  }

  str[i] = '\0';
  return str;
}

void print_str(char *str) {
  write(1, str, my_strlen(str));
}

void clear_array(char ***str) {
  for (int i = 0; (*str)[i] != NULL; i++) {
    clear_str(&(*str)[i]);
  }
}

void clear_str(char **str) {
  int len = my_strlen(*str);
  for (int i = 0; i < len; i++) {
    (*str)[i] = '\0';
  }
  (*str)[len] = '\0';
}

void del_str(char **str) {
  if (str) {
    free(*str);
    *str = NULL;
  }
  free(str);
}

void del_array(char ***str) {
  for (int i = 0; (*str)[i] != NULL; i++) {
    del_str(&(*str)[i]);
  }
  free(*(*str));
  free((*str));
}

int is_in_string(char *haystack, char *needle) {

  for (int i = 0; haystack[i] != '\0'; i++) {
    if (!my_strcmp(&haystack[i], needle)) {
      return 1;
    }
  }
  return 0;
}
