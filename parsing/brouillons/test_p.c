#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 256

char **parse_line(char *line, char *argv[], int *argc) {
  int i, j, k, in_single_quote, in_double_quote;
  *argc = 0;
  i = j = k = in_single_quote = in_double_quote = 0;
  while (line[i]) {
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r') {
      i++;
    }
    if (!line[i]) {
      break;
    }
    if (line[i] == '\'') {
      in_single_quote = !in_single_quote;
      i++;
      continue;
    }
    if (line[i] == '\"') {
      in_double_quote = !in_double_quote;
      i++;
      continue;
    }
    if (line[i] == '$' && !in_single_quote && !in_double_quote) {
      j = i + 1;
      if (line[j] == '?') {
        printf("%d", (int) getenv("?"));
        i = j + 1;
        k = j + 1;
        continue;
      }
    }
    j = i;
    while (line[j] &&
           !(line[j] == ' ' && !in_single_quote && !in_double_quote) &&
           !(line[j] == '\t' && !in_single_quote && !in_double_quote) &&
           !(line[j] == '\r') && !(line[j] == '\'') && !(line[j] == '\"')) {
      j++;
    }
    if (*argc < MAX_ARGS - 1) {
      line[j] = '\0';
      argv[(*argc)++] = &line[i];
    }
    i = j + 1;
  }
  argv[*argc] = NULL;
}

int main(int argc, char* argv[], char* envp[]) {
  if (argc != 2) {
    printf("Usage: %s <command_line>\n", argv[0]);
    return 1;
  }

  char* line = argv[1];
  char buf[32];
  char** argv_parsed = parse_line(line, envp, buf);

  int i = 0;
  while (argv_parsed[i] != NULL) {
    printf("argv[%d]: %s\n", i, argv_parsed[i]);
    i++;
  }

  return 0;
}