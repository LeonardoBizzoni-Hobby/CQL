#include "runner.h"

void execute_statement(Statement *stmt) {
  switch (stmt->type) {
  case STMT_SELECT: {} break;
  case STMT_INSERT: {} break;
  case STMT_DELETE: {} break;
  }
}
