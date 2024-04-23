#ifndef CQL_TOKEN_H
#define CQL_TOKEN_H

#include "../datatypes.h"
#include "token_type.h"

typedef struct {
  TokenType type;

  union {
    const char *identifier;
    const char *str;
    u64 integer;
    f64 real;
  } lexeme;
} Token;

#endif
