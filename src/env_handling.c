#include "env_handling.h"

void copy_env(char **str, char ***dst) {
  int elements = 0;

  while(str[elements]) {
    elements++;
  }
  (*dst) = (char **)malloc(sizeof(char *) * (elements + 1));
  for (int i = 0; i < elements; i++) {
    (*dst)[i] = my_strdup(str[i]);
  }
  (*dst)[elements] = NULL;
}

char *form_env_var(char *name, char *value) {
  char *full_env = NULL;
  char *var = NULL;

  var = my_strjoin(name, "=");
  full_env = my_strjoin(var, value);

  free(var);
  return full_env;
}

void form_path(char *path, char *file, char **full_path) {
  char *tmp_path = NULL;

  tmp_path = my_strjoin(path, "/");
  (*full_path) = my_strjoin(tmp_path, file);

  free(tmp_path);
}

void update_var_env(char *name, char *value, char ***env) {
  printf("%s %s %s\n", name, value, (*env)[0]);
}

void add_to_env_list(char *name, char *value, char ***env) {
  char **tmp = NULL;
  int elements = 0;

  while ((*env)[elements]) {
    elements++;
  }

  tmp = (char **)malloc(sizeof(char *) * (elements + 1));
  int index = 0;
  while (index < elements) {
    tmp[index] = my_strdup((*env)[index]);
    index++;
  }

  (*env) = (char **)malloc(sizeof(char *) * (elements + 2));
  for (int i = 0; i < elements; i++) {
    (*env)[i] = my_strdup(tmp[i]);
  }
  char *new_var = form_env_var(name, value);
  (*env)[elements] = my_strdup(new_var);
  (*env)[elements + 1] = NULL;

  free(new_var);
}

void rm_from_env_list(char *name, char ***env) {
  char **tmp = NULL;
  int elements = 0;

  while ((*env)[elements]) {
    elements++;
  }

  tmp = (char **)malloc(sizeof(char *) * (elements + 1));
  int index = 0;
  while (index < elements) {
    tmp[index] = my_strdup((*env)[index]);
    index++;
  }

  clear_array(&(*env));
  (*env) = (char **)malloc(sizeof(char *) * (elements + 1));

  int index_tmp = 0;
  char **tmp_var = NULL;  
  for (int i = 0; i < elements; i++) {
    my_strtrim(tmp[i], '=', &tmp_var);
    if (tmp_var[0] && my_strcmp(name, tmp_var[0]) != 0) {
      (*env)[index_tmp] = my_strdup(tmp[i]);
      index_tmp++;
    }
    clear_array(&tmp_var);
    free(tmp_var[0]);
    free(tmp_var[1]);    
    free(tmp_var);
  }
  // free(tmp_var);
  (*env)[index_tmp] = NULL;

  //clear_array(&tmp);
  //del_array(&tmp);
}
