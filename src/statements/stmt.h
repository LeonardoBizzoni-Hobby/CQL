#ifndef CQL_STATEMENT_H
#define CQL_STATEMENT_H

#include "token.h"

typedef enum {
  STMT_ALTER,
  STMT_CREATE,
  STMT_DELETE,
  STMT_INSERT,
  STMT_SELECT,
} StatementType;

typedef struct {
  Token *name;
  Token *type;
} CreateField;

typedef struct {
  StatementType type;
  Token *on_table;
  u8 field_size;

  union {
    CreateField *create;
  } fields;
} Statement;

#endif
