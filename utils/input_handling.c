#include "input_handling.h"

void clear_arr(char ***arr) {
  int e = 0;

  while ((*arr)[e]) {
    e++;
  }

  for (int i = 0; i < e; i++) {
    free((*arr)[i]);

  }
  free((*arr));
}

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

char *get_env_var_content(char *env_var, char **env) {
  char **var_env = NULL;
  char *var_value = NULL;

  for (int i = 0; env[i]; i++) {
    my_strtrim(env[i], '=', &var_env);
    var_value = my_strdup(var_env[1]);
    if (var_env[0] && !my_strcmp(env_var, var_env[0])){
      free(var_env[0]);
      free(var_env[1]);
      free(var_env);
      return var_value;
    }
    free(var_value);
    var_value = NULL;
    free(var_env[0]);
    var_env[0] = NULL;
    free(var_env[1]);
    var_env[1] = NULL;
    free(var_env);
    var_env = NULL;
  }
  return NULL;
}

char *get_env_var(char *env_var, char **env) {
  char **var_env = NULL;
  char *var_key = NULL;

  for (int i = 0; env[i]; i++) {
    my_strtrim(env[i], '=', &var_env);
    var_key = my_strdup(var_env[0]);
    if (var_key && !my_strcmp(env_var, var_key)){
      free(var_env[0]);
      free(var_env[1]);
      free(var_env);
      return var_key;
    }
    free(var_key);
    var_key = NULL;
    free(var_env[0]);
    var_env[0] = NULL;
    free(var_env[1]);
    var_env[1] = NULL;
    free(var_env);
    var_env = NULL;
  }
  return NULL;
}

void copy_env(char **str, char ***dst) {
  int e = 0;

  while (str[e]) {
    e++;
  }

  (*dst) = (char **)malloc(sizeof(char *) * e);
  int str_len = 0;
  for (int i = 0; i < e; i++) {
    str_len = my_strlen(str[i]);
    (*dst)[i] = (char *)malloc(sizeof(char) * (str_len + 1));
    for (int j = 0; j < str_len; j++) {
      (*dst)[i][j] = str[i][j];
    }
    (*dst)[i][str_len] = '\0';
  }

  (*dst)[e] = NULL;
}

char *form_env_var(char *name, char *value) {
  char *full_env = NULL;
  char *var = NULL;

  var = my_strjoin(name, "=");
  full_env = my_strjoin(var, value);

  free(var);
  return full_env;
}

void update_var_env(char *name, char *value, char ***env) {
  char **tmp = NULL;
  char **trimed = NULL;
  char *new_env_var = NULL;
  int e = 0;

  while ((*env)[e]) {
    e++;
  }

  copy_env((*env), &tmp);
  clear_arr(env);

  (*env) = NULL;
  (*env) = (char **)malloc(sizeof(char *) * e);
  int str_len = 0;
  for (int i = 0; i < e; i++) {
    my_strtrim(tmp[i], '=', &trimed);
    if (!my_strcmp(trimed[0], name)) {
      new_env_var = form_env_var(name, value);
      str_len = my_strlen(new_env_var);
      (*env)[i] = (char *)malloc(sizeof(char) * (str_len + 1));
      for (int j = 0; j < str_len; j++) {
        (*env)[i][j] = new_env_var[j];
      }
      free(new_env_var);
    }
    else {
      str_len = my_strlen(tmp[i]);
      (*env)[i] = (char *)malloc(sizeof(char) * (str_len + 1));
      for (int j = 0; j < str_len; j++) {
        (*env)[i][j] = tmp[i][j];
      }
      (*env)[i][str_len] = '\0';
    }

    free(trimed[0]);
    free(trimed[1]);
    free(trimed);

  }
  clear_arr(&tmp);
}

void add_to_env_list(char *name, char *value, char ***env) {
  char **tmp = NULL;
  int e = 0;

  while ((*env)[e]) {
    e++;
  }

  copy_env((*env), &tmp);
  clear_arr(env);

  (*env) = NULL;
  (*env) = (char **)malloc(sizeof(char *) * (e + 2));
  int str_len = 0;
  for (int i = 0; i < e; i++) {
    str_len = my_strlen(tmp[i]);
    (*env)[i] = (char *)malloc(sizeof(char) * (str_len + 1));
    for (int j = 0; j < str_len; j++) {
      (*env)[i][j] = tmp[i][j];
    }
    (*env)[i][str_len] = '\0';
  }

  char *var = my_strjoin(name, "=");
  char *full_var = my_strjoin(var, value);
  (*env)[e] = my_strdup(full_var);
  (*env)[(e + 1)] = NULL;
  free(var);
  free(full_var);

  clear_arr(&tmp);
}
