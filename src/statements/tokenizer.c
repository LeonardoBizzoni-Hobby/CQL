#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_type.h"
#include "tokenizer.h"

Token *get_token(char **command) {
  u64 start = 0;
  skip_whitespace(&start, *command);

  char ch = advance(&start, *command);
  if (is_digit(ch)) {
    return make_number_token(&start, *command);
  } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
    return make_identifier_token(&start, *command);
  }

  Token *token = 0;
  switch (ch) {
    case '(': {
      token = make_token(LEFT_PAREN);
    } break;
    case ')': {
      token = make_token(RIGHT_PAREN);
    } break;
    case ',': {
      token = make_token(COMMA);
    } break;
    case '"': {
      u64 curr = start;
      while ((*command)[curr] != 0 && (*command)[curr] != '"') {
	printf("%i - %c\n", (*command)[curr], (*command)[curr]);
        advance(&curr, *command);
      }

      if ((*command)[curr] == '"') {
	token = make_token(STRING);
        token->lexeme.str = get_substr(*command, start, curr);
        advance(&curr, *command);
      }

      start = curr;
    } break;
  }

  *command += start;
  return token;
}

Token *make_token(TokenType type) {
  Token *token = malloc(sizeof(Token));
  token->type = type;

  return token;
}

Token *make_number_token(u64 *idx, char *command) {
  Token *token = 0;
  u64 start = *idx - 1;

  while (is_digit(command[*idx])) {
    advance(idx, command);
  }

  if (command[*idx] == '.' && is_digit(command[*idx + 1])) {
    advance(idx, command);
    while (is_digit(command[*idx])) {
      advance(idx, command);
    }

    token = make_token(REAL);
    token->lexeme.real = atof(get_substr(command, start, *idx));
  } else {
    token = make_token(INTEGER);
    token->lexeme.integer = atoi(get_substr(command, start, *idx));
  }

  return token;
}

/* TODO: scan identifiers and detect keywords */
Token *make_identifier_token(u64 *idx, char *command) { return 0; }

char advance(u64 *idx, const char *command) {
  if (!command[*idx]) {
    return 0;
  }

  return command[(*idx)++];
}

void skip_whitespace(u64 *idx, const char *command) {
  while (1) {
    switch (command[*idx]) {
    case ' ':
    case '\t':
    case '\n':
    case '\r': {
      (*idx)++;
    } break;
    default:
      return;
    }
  }
}

bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

char *get_substr(const char *command, u64 start, u64 end) {
  char *substr = malloc(sizeof(char) * (end - start + 1));

  for (u64 i = start; i <= end; i++) {
    substr[i - start] = command[i];
  }
  substr[end - start] = '\0';

  return substr;
}
