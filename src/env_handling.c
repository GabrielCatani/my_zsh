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
  char **var_elements = NULL;
  char *new_var = NULL;

  for (int i = 0; (*env)[i] != NULL; i++) {
      my_strtrim((*env)[i], '=', &var_elements);
      if (!my_strcmp(var_elements[0], name)) {
          new_var = form_env_var(name, value);          
          free((*env)[i]);
          (*env)[i] = NULL;
          (*env)[i] = my_strdup(new_var);
          free(new_var);
      }
      for (int j = 0; var_elements[j] != NULL; j++) {
          free(var_elements[j]);
      }
      free(var_elements);
      var_elements = NULL;
  }
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

  //del_array(env);

  for (int i = 0; (*env)[i] ; i++) {
      free((*env)[i]);
  }
  free((*env));
  (*env) = (char **)malloc(sizeof(char *) * (elements + 2));
  for (int i = 0; i < elements; i++) {
    (*env)[i] = my_strdup(tmp[i]);
  }
  char *new_var = form_env_var(name, value);
  (*env)[elements] = my_strdup(new_var);
  (*env)[elements + 1] = NULL;
  
  for (int i = 0; i < elements; i++) {
      free(tmp[i]);
  }
   free(tmp);
  //del_array(&tmp);
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

  //clear_array(&(*env));
  //del_array(env);
  for (int i = 0; (*env)[i] ; i++) {
      free((*env)[i]);
  }
  free((*env));  
  (*env) = (char **)malloc(sizeof(char *) * (elements + 1));

  int index_tmp = 0;
  char **tmp_var = NULL;  
  for (int i = 0; i < elements; i++) {
    my_strtrim(tmp[i], '=', &tmp_var);
    if (tmp_var[0] && my_strcmp(name, tmp_var[0]) != 0) {
      (*env)[index_tmp] = my_strdup(tmp[i]);
      index_tmp++;
    }
    for (int j = 0; tmp_var[j]; j++) {
        free(tmp_var[j]);
    }
    free(tmp_var);
  }
  // free(tmp_var);
  (*env)[index_tmp] = NULL;
  for (int i = 0; i < elements; i++) {
      free(tmp[i]);
  }
  free(tmp);
}
