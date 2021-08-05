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

char **copy_env(char **env) {
  int elements = 0;
  char **copy_env = NULL;

  while (env[elements]) {
    elements++;
  }

  copy_env = (char **)malloc(sizeof(char *) * elements);

  for (int i = 0; i <= elements; i++) {
    copy_env[i] = my_strdup(env[i]);
  }

  return copy_env;
}

void add_to_env_list(char *name, char *value, char ***env) {
  char **tmp = NULL;
  int nbr_e = 0;

  while ((*env)[nbr_e]) {
    nbr_e++;
  }

  tmp = copy_env((*env));
  for (int i = 0; i < nbr_e; i++) {
    free((*env)[i]);
    (*env)[i] = NULL;
  }
  free((*env));
  (*env) = NULL;

  (*env) = (char **)malloc(sizeof(char *) * (nbr_e + 1));
  for (int i = 0; i < nbr_e; i++) {
    (*env)[i] = my_strdup(tmp[i]);
    free(tmp[i]);
    tmp[i] = NULL;
  }
  free(tmp);
  tmp = NULL;

  char *var = my_strjoin(name, "=");
  char *full_var = my_strjoin(var, value);

  (*env)[nbr_e] = my_strdup(full_var);
  free(var);
  free(full_var);
}
