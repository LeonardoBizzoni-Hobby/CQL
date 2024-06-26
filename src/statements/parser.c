#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "stmt.h"
#include "token.h"
#include "token_type.h"
#include "tokenizer.h"

#define MATCH(token, expected_type)                                            \
  if (!token || token->type != expected_type) {                                \
    return STMT_PARSE_INVALID;                                                 \
  }

StmtParseResult parse_statement(Statement *stmt, char *command) {
  Token *token = 0;
  if ((token = get_token(&command))) {
    switch (token->type) {
    case ALTER: {
      stmt->type = STMT_ALTER;

    } break;
    case CREATE: {
      stmt->type = STMT_CREATE;
      return parse_create(stmt, &command);
    } break;
    case DELETE: {
      stmt->type = STMT_DELETE;
      return parse_delete(stmt, &command);
    } break;
    case INSERT: {
      stmt->type = STMT_INSERT;
      return parse_insert(stmt, &command);
    } break;
    case SELECT: {
      stmt->type = STMT_SELECT;
      return parse_select(stmt, &command);
    } break;
    default: {
      return STMT_PARSE_INVALID;
    }
    }
  }

  return STMT_PARSE_OK;
}

StmtParseResult parse_create(Statement *stmt, char **command) {
  Token *token = get_token(command);
  MATCH(token, IDENTIFIER);
  stmt->on_table = token;

  token = get_token(command);
  MATCH(token, LEFT_PAREN);

  CreateField *fields = 0;
  if ((token = get_token(command)) && token->type != RIGHT_PAREN) {
    do {
      MATCH(token, IDENTIFIER);

      Token *type = get_token(command);
      switch (type->type) {
      case TYPE_INTEGER:
      case TYPE_REAL:
      case TYPE_STRING:
        break;
      default:
        return STMT_PARSE_INVALID;
      }

      if (!fields) {
        fields = malloc(sizeof(CreateField));
      } else {
        fields = realloc(fields, (stmt->field_size + 1) * sizeof(CreateField));
      }
      fields[stmt->field_size].name = token;
      fields[stmt->field_size++].type = type;

      token = get_token(command);
    } while (token->type == COMMA && (token = get_token(command)));
  }

  MATCH(token, RIGHT_PAREN);

  /* There should be no other token after the `)` */
  if (get_token(command)) {
    return STMT_PARSE_INVALID;
  }
  stmt->fields.create = fields;

  return STMT_PARSE_OK;
}

StmtParseResult parse_delete(Statement *stmt, char **command) {
  Token *token = get_token(command);
  MATCH(token, IDENTIFIER);
  stmt->on_table = token;

  /* There should be no other token after the table name */
  if (get_token(command)) {
    return STMT_PARSE_INVALID;
  }

  return STMT_PARSE_OK;
}

StmtParseResult parse_insert(Statement *stmt, char **command) {
  Token *token = 0;
  InsertField *values = 0;

  token = get_token(command);
  MATCH(token, LEFT_PAREN);
  token = get_token(command);

  do {
    switch (token->type) {
    case INTEGER:
    case REAL:
    case STRING:
      break;
    default:
      return STMT_PARSE_INVALID;
    }

    if (!values) {
      values = malloc(sizeof(InsertField));
    } else {
      values = realloc(values, (stmt->field_size + 1) * sizeof(InsertField));
    }
    values[stmt->field_size++].value = token;

    token = get_token(command);
  } while (token->type == COMMA && (token = get_token(command)));
  stmt->fields.insert = values;

  MATCH(token, RIGHT_PAREN);

  token = get_token(command);
  MATCH(token, INTO);

  token = get_token(command);
  MATCH(token, IDENTIFIER);
  stmt->on_table = token;

  /* There should be no other token after the table name */
  if (get_token(command)) {
    return STMT_PARSE_INVALID;
  }
  return STMT_PARSE_OK;
}

StmtParseResult parse_select(Statement *stmt, char **command) {
  return STMT_PARSE_OK;
}
