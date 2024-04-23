#ifndef CQL_STATEMENT_H
#define CQL_STATEMENT_H

typedef enum {
  STMT_SELECT,
  STMT_INSERT,
  STMT_CREATE,
  STMT_DELETE,
} StatementType;

typedef struct {
  StatementType type;
} Statement;

#endif
