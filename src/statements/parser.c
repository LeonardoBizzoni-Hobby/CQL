#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "stmt.h"
#include "token.h"
#include "tokenizer.h"

StmtParseResult parse_statement(Statement *stmt, char *command) {
  Token *token = get_token(&command);
  if (token->type == INTEGER) {
    printf("Integer token found: %llu\n", token->lexeme.integer);
  } else if (token->type == REAL) {
    printf("Real number token found: %f\n", token->lexeme.real);
  } else if (token->type == STRING) {
    printf("String token found: %s\n", token->lexeme.str);
  }

  printf("Rest of command: %s\n", command);

  return STMT_PARSE_OK;
}
