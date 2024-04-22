#ifndef CQL_PARSER_H
#define CQL_PARSER_H

#include "stmt.h"

typedef enum {
  STMT_PARSE_OK,
  STMT_PARSE_UNRECOGNIZED,
} StmtParseResult;

StmtParseResult parse_statement(Statement *, const char *);

#endif