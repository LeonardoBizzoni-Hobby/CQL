#ifndef CQL_TOKEN_H
#define CQL_TOKEN_H

#include "../datatypes.h"
#include "token_type.h"

typedef struct {
  TokenType type;

  union {
    char *identifier;
    char *str;
    u64 integer;
    f64 real;
  } lexeme;
} Token;

#endif
