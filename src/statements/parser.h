#ifndef CQL_PARSER_H
#define CQL_PARSER_H

#include "stmt.h"

typedef enum {
  STMT_PARSE_OK,
  STMT_PARSE_INVALID,
  STMT_PARSE_UNRECOGNIZED,
} StmtParseResult;

StmtParseResult parse_statement(Statement *, char *);

StmtParseResult parse_create(Statement *, char **);
StmtParseResult parse_delete(Statement *, char **);
StmtParseResult parse_insert(Statement *, char **);
StmtParseResult parse_select(Statement *, char **);

#endif
