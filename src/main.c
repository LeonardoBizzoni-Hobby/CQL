#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "datatypes.h"
#include "metacommand/metacommand.h"
#include "statements/stmt.h"
#include "statements/parser.h"
#include "runner/runner.h"

int main(void) {
  while (1) {
    printf("λ> ");

    char *command = read_command();
    if (!command) {
      fprintf(stderr, "Memory allocation for CQL command failed.");
      free(command);
      exit(EXIT_FAILURE);
    }

    if (command[0] == '.') {
      switch (execute_metacommand(command)) {
      case (METACOMMAND_SUCCESS): break;
      case (METACOMMAND_UNRECOGNIZED): {
        fprintf(stderr, "Unrecognized meta-command `%s`\n", command);
      } break;
      }
    } else {
      Statement stmt = {0};

      switch (parse_statement(&stmt, command)) {
      case (STMT_PARSE_OK): {
	execute_statement(&stmt);
	printf("Executed.\n");
      } break;
      case (STMT_PARSE_UNRECOGNIZED): {
	fprintf(stderr, "Unrecognized CQL statement at start of `%s`.\n", command);
      } break;
      }
    }

    free(command);
  }
}

char *read_command() {
  u64 capacity = 1;
  char *command = (char *)malloc(capacity * sizeof(char));
  if (!command) {
    fprintf(stderr, "Memory allocation for CQL command failed.");
    free(command);
    exit(EXIT_FAILURE);
  }

  char ch;
  u64 len = 0;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (len >= capacity - 1) {
      REALLOC_CHECK(command, capacity *= 2);
    }

    command[len++] = ch;
  }

  if (ch == EOF) {
    exit(EXIT_SUCCESS);
  }

  command[len++] = '\0';
  REALLOC_CHECK(command, len);

  return command;
}
