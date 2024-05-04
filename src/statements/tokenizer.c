#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_type.h"
#include "tokenizer.h"

Token *get_token(char **command) {
  u64 start = 0;
  Token *token = 0;
  skip_whitespace(&start, *command);

  char ch = advance(&start, *command);
  if (is_digit(ch)) {
    token = make_number_token(&start, *command);
  } else if (is_alphabetic(ch)) {
    token = make_identifier_token(&start, *command);
  } else {
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

Token *make_identifier_token(u64 *idx, char *command) {
  Token *token = 0;
  u64 start = *idx - 1;

  while (is_alphanumeric(command[*idx])) {
    advance(idx, command);
  }

  char *lexeme = get_substr(command, start, *idx);
  token = make_token(typeof_identifier(lexeme));
  token->lexeme.identifier = lexeme;

  return token;
}

TokenType typeof_identifier(const char *lexeme) {
  switch (lexeme[0]) {
  case 'a': {
    if (compare_lexeme(1, 4, lexeme, "alter")) {
      return ALTER;
    }
  } break;
  case 'c': {
    if (compare_lexeme(1, 5, lexeme, "create")) {
      return CREATE;
    }
  } break;
  case 'd': {
    if (compare_lexeme(1, 5, lexeme, "delete")) {
      return DELETE;
    }
  } break;
  case 'i': {
    switch (lexeme[1]) {
    case 'n': {
      switch (lexeme[2]) {
      case 's': {
        if (compare_lexeme(3, 3, lexeme, "insert")) {
          return INSERT;
        }
      } break;
      case 't': {
        switch (lexeme[3]) {
        case 'o': {
          if (compare_lexeme(4, 0, lexeme, "into")) {
            return INTO;
          }
        } break;
        case 'e': {
          if (compare_lexeme(4, 3, lexeme, "integer")) {
            return TYPE_INTEGER;
          }
        } break;
        }
      } break;
      }
    } break;
    }
  } break;
  case 'r': {
    if (compare_lexeme(1, 3, lexeme, "real")) {
      return TYPE_REAL;
    }
  } break;
  case 's': {
    switch (lexeme[1]) {
    case 'e': {
      if (compare_lexeme(2, 4, lexeme, "select")) {
        return SELECT;
      }
    } break;
    case 't': {
      if (compare_lexeme(2, 4, lexeme, "string")) {
        return TYPE_STRING;
      }
    } break;
    }
  }
  }

  return IDENTIFIER;
}

bool compare_lexeme(u8 start, u8 ends_in, const char *found,
                    const char *wanted) {
  return !strncmp(found + start, wanted + start, ends_in) &&
         found[start + ends_in] == 0;
}

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

bool is_alphabetic(char ch) {
  return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_';
}

bool is_alphanumeric(char ch) { return is_alphabetic(ch) || is_digit(ch); }

char *get_substr(const char *command, u64 start, u64 end) {
  char *substr = malloc(sizeof(char) * (end - start + 1));

  for (u64 i = start; i <= end; i++) {
    substr[i - start] = command[i];
  }
  substr[end - start] = '\0';

  return substr;
}
