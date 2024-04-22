#include <string.h>

#include "parser.h"
#include "stmt.h"

StmtParseResult parse_statement(Statement *stmt, const char *command) {
  if (!strncmp(command, "select", 6)) {
    stmt->type = STMT_SELECT;
    return STMT_PARSE_OK;
  } else if (!strncmp(command, "insert", 6)) {
    stmt->type = STMT_INSERT;
    return STMT_PARSE_OK;
  } else if (!strncmp(command, "delete", 6)) {
    stmt->type = STMT_DELETE;
    return STMT_PARSE_OK;
  } else {
    return STMT_PARSE_UNRECOGNIZED;
  }
}
