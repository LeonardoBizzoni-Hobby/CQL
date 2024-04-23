#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

Token *get_token(char *command) {
  u64 i = 0;
  skip_whitespace(&i, command);

  char ch = advance(&i, command);
  if (is_digit(ch)) {
    return make_number_token(&i, command);
  } else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
    return make_identifier_token(&i, command);
  }

  return 0;
}

Token *make_number_token(u64 *idx, char *command) {
  Token *token = malloc(sizeof(Token));
  u64 start = *idx - 1;

  while (is_digit(command[*idx])) {
    advance(idx, command);
  }

  if (command[*idx] == '.' && is_digit(command[*idx + 1])) {
    token->type = REAL;

    advance(idx, command);
    while (is_digit(command[*idx])) {
      advance(idx, command);
    }

    token->lexeme.real = atof(get_substr(command, start, *idx));
    return token;
  } else {
    token->type = INTEGER;
    token->lexeme.integer = atoi(get_substr(command, start, *idx));

    return token;
  }

  return 0;
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
