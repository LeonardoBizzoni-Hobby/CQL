#ifndef CQL_TOKEN_TYPE_H
#define CQL_TOKEN_TYPE_H

typedef enum {
  ALTER,
  CREATE,
  DELETE,
  INSERT,
  SELECT,

  INTO,
  FROM,
  WHERE,

  LEFT_PAREN,
  RIGHT_PAREN,
  COMMA,

  IDENTIFIER,
  STRING,
  INTEGER,
  REAL,

  TYPE_STRING,
  TYPE_INTEGER,
  TYPE_REAL,
} TokenType;

#endif
