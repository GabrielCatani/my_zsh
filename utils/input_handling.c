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

char *get_env_var_content(char *env_var, char **env) {
  char **var_env = NULL;
  char *var_value = NULL;

  for (int i = 0; env[i]; i++) {
    var_env = my_strtrim(env[i], '=');
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
    var_env = my_strtrim(env[i], '=');
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


void update_var_env(char *name, char *value, char **env) {
  char **tmp = NULL;
  int nbr_e = 0;

  while (env[nbr_e]) {
    nbr_e++;
  }

  copy_env(env, &tmp);
  for (int i = 0; i < nbr_e; i++) {
    free(env[i]);
    env[i] = NULL;
  }
  free(env);
  env = NULL;

  env = (char **)malloc(sizeof(char *) * (nbr_e));
  char *env_var = NULL;
  char *var = NULL;
  char *full_var = NULL;

  for (int i = 0; i < nbr_e; i++) {
    env_var = get_env_var(name, tmp);
    if (env_var && !my_strcmp(env_var, name)) {
      var = my_strjoin(name, "=");
      full_var = my_strjoin(var, value);
      env[i] = my_strdup(full_var);
      free(var);
      free(full_var);
    }
    else {
      env[i] = my_strdup(tmp[i]);;
    }
    free(tmp[i]);
    tmp[i] = NULL;
  }
  free(tmp);
  tmp = NULL;
}

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
