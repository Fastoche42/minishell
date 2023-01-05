#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

#define MAX_LINE_LENGTH 1024

// Structure pour la liste chainée des commandes
struct command {
  char *cmd;
  int redirect_input;  // 1 si la commande doit rediriger l'entrée, 0 sinon
  char *input_filename;  // Nom du fichier d'entrée
  int redirect_output;  // 1 si la commande doit rediriger la sortie, 0 sinon
  char *output_filename;  // Nom du fichier de sortie
  int append_output;  // 1 si la commande doit ajouter à la sortie, 0 sinon
  struct command *next;
};

// Fonction pour ajouter une commande à la liste chainée
void add_command(struct command **head, char *cmd) {
  struct command *new_node = malloc(sizeof(struct command));
  new_node->cmd = cmd;
  new_node->redirect_input = 0;
  new_node->input_filename = NULL;
  new_node->redirect_output = 0;
  new_node->output_filename = NULL;
  new_node->append_output = 0;
  new_node->next = *head;
  *head = new_node;
}

// Fonction pour exécuter une commande "cd"
void execute_cd(char *dir) {
  if (dir == NULL) {
    fprintf(stderr, "cd: missing argument\n");
  } else if (chdir(dir) != 0) {
    perror("cd");
  }
}

// Fonction pour exécuter une commande "pwd"
void execute_pwd() {
  char cwd[MAX_LINE_LENGTH];
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("pwd");
  } else {
    printf("%s\n", cwd);
  }
}

// Fonction pour exécuter une commande "more"
void execute_more(char *filename) {
  if (filename == NULL) {
    fprintf(stderr, "more: missing argument\n");
  } else {
    char *argv[] = {"more", filename, NULL};
    execvp("more", argv);
  }
}

// Fonction pour exécuter une commande "echo"
void execute_echo(struct command *cmd_list) {
  struct command *current = cmd_list;
  while (current != NULL) {
    printf("%s ", current->cmd);
    current = current->next;
  }
  printf("\n");
}

// Fonction pour exécuter une commande "env"
void execute_env() {
  extern char **environ;
  for (char **env = environ; *env != 0; env++) {
    printf("%s\n", *env);
  }
}

// Fonction pour exécuter une commande "export"
void execute_export(char *var) {
  if (var == NULL) {
    fprintf(stderr, "export: missing argument\n");
  } else {
    putenv(var);
  }
}

// Fonction pour exécuter une commande "unset"
void execute_unset(char *var) {
  if (var == NULL) {
    fprintf(stderr, "unset: missing argument\n");
  } else {
    unsetenv(var);
  }
}

// Fonction pour trouver le prochain mot dans une chaîne de caractères
// en prenant en compte les simples quotes et doubles quotes
char *next_word(char *str) {
  int in_single_quote = 0;
  int in_double_quote = 0;
  for (char *p = str; *p != '\0'; p++) {
    if (*p == '\'' && !in_double_quote) {
      in_single_quote = !in_single_quote;
    } else if (*p == '\"' && !in_single_quote) {
      in_double_quote = !in_double_quote;
    } else if (*p == ' ' && !in_single_quote && !in_double_quote) {
      *p = '\0';
      return p + 1;
    }
  }
  return NULL;
}

int main(int argc, char **argv) {
  int fd[2];
  // Boucle infinie pour lire et exécuter les commandes de l'utilisateur
  while (1) {
    // Afficher le prompt
    //char *prompt = getenv("USER");
    //prompt = strcat(prompt, "@");
    //prompt = strcat(prompt, getenv("HOSTNAME"));
    //prompt = strcat(prompt, " $ ");
    char *line = readline(" $  ");
    if (line == NULL) {
      break;
    }

    // Ajouter la ligne à l'historique
    add_history(line);

    // Séparer la ligne en mots séparés par des espaces
    char *word = strtok(line, " ");

    // Créer une liste chainée pour stocker les mots de la ligne
    struct command *cmd_list = NULL;
    while (word != NULL) {
      // Récupérer le prochain mot
      char *next = next_word(word);

      // Ajouter le mot à la liste chainée
      add_command(&cmd_list, word);

      // Lire le prochain mot
      word = strtok(next, " ");
    }

    // Si la liste est vide, passer à la prochaine itération
    if (cmd_list == NULL) {
      continue;
    }

    // Si la commande contient un pipe, la diviser en plusieurs commandes
    struct command *current = cmd_list;
    while (current != NULL) {
      if (strcmp(current->cmd, "|") == 0) {
        current->cmd = NULL;
        current = current->next;
      }
      current = current->next;
    }

    // Exécuter chaque commande séparément
    int fd_in = 0;
    for (current = cmd_list; current != NULL; current = current->next) {
      // Créer un tableau d'arguments pour execvp
      int i = 0;
      char *argv[MAX_LINE_LENGTH];
      for (struct command *p = current; p != NULL && p->cmd != NULL; p = p->next) {
        argv[i] = p->cmd;
        i++;
      }
      argv[i] = NULL;

      // Exécuter la commande
      int fd_out;
      if (current->next != NULL && current->next->cmd != NULL) {
        // Créer un pipe si la commande suivante existe
        int fd[2];
        if (pipe(fd) == -1) {
          perror("pipe");
          exit(1);
        }
        fd_out = fd[1];
      } else {
        // Sinon, rediriger la sortie vers le fichier ou la sortie standard
        if (current->redirect_output) {
          if (current->append_output) {
            fd_out = open(current->output_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
          } else {
            fd_out = open(current->output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
          }
          if (fd_out == -1) {
            perror(current->output_filename);
            exit(1);
          }
        } else {
          fd_out = STDOUT_FILENO;
        }
      }

      // Vérifier si la commande est un builtin
      if (strcmp(argv[0], "cd") == 0) {
        execute_cd(argv[1]);
      } else if (strcmp(argv[0], "pwd") == 0) {
        execute_pwd();
      } else if (strcmp(argv[0], "more") == 0) {
        execute_more(argv[1]);
      } else if (strcmp(argv[0], "echo") == 0) {
        execute_echo(current);
      } else if (strcmp(argv[0], "env") == 0) {
        execute_env();
      } else if (strcmp(argv[0], "export") == 0) {
        execute_export(argv[1]);
      } else if (strcmp(argv[0], "unset") == 0) {
        execute_unset(argv[1]);
      } else {
        // Si la commande n'est pas un builtin, exécuter le programme externe
        int pid = fork();
        if (pid == 0) {
          // Processus fils
          if (current->redirect_input) {
            // Rediriger l'entrée depuis le fichier
            int fd = open(current->input_filename, O_RDONLY);
            if (fd == -1) {
              perror(current->input_filename);
              exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
          } else {
            // Rediriger l'entrée depuis le pipe précédent
            dup2(fd_in, STDIN_FILENO);
          }
          if (current->next != NULL && current->next->cmd != NULL) {
            // Rediriger la sortie vers le pipe suivant
            dup2(fd_out, STDOUT_FILENO);
          } else {
            // Rediriger la sortie vers le fichier ou la sortie standard
            if (current->redirect_output) {
              dup2(fd_out, STDOUT_FILENO);
            }
          }
          execvp(argv[0], argv);
          perror(argv[0]);
          exit(1);
        } else if (pid < 0) {
          // Erreur
          perror("fork");
          exit(1);
        } else {
          // Processus père
          close(fd_in);
          close(fd_out);
          waitpid(pid, NULL, 0);
        }
      }

      // Fermer le pipe précédent et utiliser le pipe suivant comme entrée
      if (current->next != NULL && current->next->cmd != NULL) {
        close(fd_in);
        fd_in = fd[0];
      }
    }
  }

  return 0;
}
