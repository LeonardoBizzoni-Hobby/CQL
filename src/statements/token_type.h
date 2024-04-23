#ifndef CQL_TOKEN_TYPE_H
#define CQL_TOKEN_TYPE_H

typedef enum {
  SELECT,
  INSERT,
  CREATE,
  ALTER,
  DELETE,

  INTO,

  LEFT_PAREN,
  RIGHT_PAREN,
  COMMA,

  IDENTIFIER,
  STRING,
  INTEGER,
  REAL,
} TokenType;

#endif
