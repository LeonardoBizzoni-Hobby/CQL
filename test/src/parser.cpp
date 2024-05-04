#include <gtest/gtest.h>

extern "C" {
  #include <string.h>
  #include "statements/parser.h"
}

TEST(Parsing, NoCommand) {
  Statement stmt;
  const char *command = "";

  ASSERT_EQ(parse_statement(&stmt, (char *)command), STMT_PARSE_OK);
}

TEST(Parsing, CreateEmptyTable) {
  Statement stmt;
  stmt.field_size = 0;
  const char *command = "create table()";

  ASSERT_EQ(parse_statement(&stmt, (char *)command), STMT_PARSE_OK);
  ASSERT_TRUE(!strcmp(stmt.on_table->lexeme.identifier, "table"));
  ASSERT_EQ(stmt.field_size, 0);
}

TEST(Parsing, CreateTableWithFields) {
  Statement stmt;
  stmt.field_size = 0;
  const char *command = "create table(field1 integer, field2 real,field3 "
                        "string,field4 integer,field5 real,field6 string)";

  ASSERT_EQ(parse_statement(&stmt, (char *)command), STMT_PARSE_OK);
  ASSERT_EQ(stmt.type, STMT_CREATE);
  ASSERT_TRUE(!strcmp(stmt.on_table->lexeme.identifier, "table"));
  ASSERT_EQ(stmt.field_size, 6);

  ASSERT_TRUE(!strcmp(stmt.fields.create[0].name->lexeme.identifier, "field1"));
  ASSERT_TRUE(!strcmp(stmt.fields.create[1].name->lexeme.identifier, "field2"));
  ASSERT_TRUE(!strcmp(stmt.fields.create[2].name->lexeme.identifier, "field3"));
  ASSERT_TRUE(!strcmp(stmt.fields.create[3].name->lexeme.identifier, "field4"));
  ASSERT_TRUE(!strcmp(stmt.fields.create[4].name->lexeme.identifier, "field5"));
  ASSERT_TRUE(!strcmp(stmt.fields.create[5].name->lexeme.identifier, "field6"));

  ASSERT_EQ(stmt.fields.create[0].type->type, TYPE_INTEGER);
  ASSERT_EQ(stmt.fields.create[1].type->type, TYPE_REAL);
  ASSERT_EQ(stmt.fields.create[2].type->type, TYPE_STRING);
  ASSERT_EQ(stmt.fields.create[3].type->type, TYPE_INTEGER);
  ASSERT_EQ(stmt.fields.create[4].type->type, TYPE_REAL);
  ASSERT_EQ(stmt.fields.create[5].type->type, TYPE_STRING);
}

TEST(Parsing, DeleteTable) {
  Statement stmt;
  const char *command = "delete table";

  ASSERT_EQ(parse_statement(&stmt, (char *)command), STMT_PARSE_OK);
  ASSERT_EQ(stmt.type, STMT_DELETE);
  ASSERT_TRUE(!strcmp(stmt.on_table->lexeme.identifier, "table"));
}

TEST(Parsing, DeleteWithoutTableName) {
  Statement stmt;
  const char *command = "delete create";

  ASSERT_EQ(parse_statement(&stmt, (char *)command), STMT_PARSE_INVALID);
}
