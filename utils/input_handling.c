#include "input_handling.h"

int count_nodes (struct AST_Lexer *ast) {
  int nbr_nodes = 0;
  ASTNode *ptr = NULL;

  ptr = ast->root->left;
  while (ptr) {
    nbr_nodes++;
    ptr = ptr->left;
  }

  ptr = ast->root->right;
  while (ptr) {
    nbr_nodes++;
    ptr = ptr->right;
  }

  return nbr_nodes;
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
  char **full_var = NULL;
  char *content = NULL;
  int index = 0;

  while (env[index]) {
    my_strtrim(env[index], '=', &full_var);
    if (!(my_strcmp(env_var, full_var[0]))) {
      content = my_strdup(full_var[1]);
      for (int i = 0; full_var[i] != NULL; i++) {
          free(full_var[i]);
      }
      free(full_var);
      return content;
    }
    for (int i = 0; full_var[i] != NULL; i++) {
        free(full_var[i]);
    }
    free(full_var);
    index++;
  }

  return NULL;
}

char *get_env_var(char *env_var, char **env) {
  char **full_var = NULL;
  char *content = NULL;
  int index = 0;

  while (env[index]) {
    my_strtrim(env[index], '=', &full_var);
    if (!(my_strcmp(env_var, full_var[0]))) {
      content = my_strdup(full_var[0]);
      for (int i = 0; full_var[i] != NULL; i++) {
          free(full_var[i]);
      }
      free(full_var);
      return content;
    }
    for (int i = 0; full_var[i] != NULL; i++) {
        free(full_var[i]);
    }
    free(full_var);
    full_var = NULL;
    index++;
  }

  return NULL;
}

void get_bin_src_from_path(char *PATH, char ***bin_paths) {
  char **full_paths = NULL;

  my_strtrim(PATH, ':', &full_paths);
  int elements = 0;
  while (full_paths[elements]) {
    elements++;
  }
  (*bin_paths) = (char **)malloc(sizeof(char *) * (elements + 1));
  int i = 0;
  int index = 0;

  while (full_paths[i] != NULL) {
    if (is_in_string(full_paths[i], "bin")) {
      (*bin_paths)[index] = my_strdup(full_paths[i]);
      index++;
     }
    i++;
  }
  (*bin_paths)[index] = NULL;
  clear_array(&full_paths);
  del_array(&full_paths);
}

int is_in_dir(char *dir_name, char *file_name) {
  DIR *dir_path = opendir(dir_name);
  struct dirent *file = NULL;

  if (!dir_path) {
    return 0;
  }
  while ((file = readdir(dir_path))) {
    if (!(my_strcmp(file->d_name, file_name))) {
      closedir(dir_path);
      return 1;
    }
  }
  closedir(dir_path);

  return 0;
}

void form_args(struct AST_Lexer *ast, char ***args) {
  int elements = 0;
  ASTNode *ptr = NULL;
  int index = 0;
  
  elements = count_nodes(ast);
  (*args) = (char **)malloc(sizeof(char *) * (elements + 2));

  (*args)[index] = my_strdup(ast->root->content);
  
  index++;
  ptr = ast->root->left;
  while (ptr) {
    (*args)[index] = my_strdup(ptr->content);
    ptr = ptr->left;
    index++;
  }

  ptr = ast->root->right;
  while (ptr) {
    (*args)[index] = my_strdup(ptr->content);
    ptr = ptr->right;
    index++;
  }

  (*args)[index] = NULL;
}

void convert_home(char **input, char **env) {
  char *tmp = NULL;
  char *home = NULL;
  char *home_tmp = NULL;
  
  tmp = my_strdup((*input));
  free((*input));
  
  home = get_env_var_content("HOME", env);

  home_tmp = my_strjoin(home, "/");
  free(home);
  (*input) = my_strjoin(home_tmp, &tmp[1]);
  free(home_tmp);
  free(tmp);
}
