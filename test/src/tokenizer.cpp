#include <gtest/gtest.h>

extern "C" {
  #include <string.h>

  #include "statements/tokenizer.h"
  #include "statements/token_type.h"
}

TEST(Tokenizer, TokenSequence) {
  const char *command = "(,)";

  ASSERT_EQ(get_token((char **)&command)->type, LEFT_PAREN);
  ASSERT_EQ(get_token((char **)&command)->type, COMMA);
  ASSERT_EQ(get_token((char **)&command)->type, RIGHT_PAREN);
  ASSERT_EQ(get_token((char **)&command), (void *)0);
}

TEST(Tokenizer, InvalidSyntaxForRealNumbers) {
  const char *command = "2. 4,3";

  Token *tk = get_token((char **)&command);
  ASSERT_EQ(tk->type, INTEGER);
  ASSERT_EQ(tk->lexeme.integer, 2);

  // The '.' is an error
  ASSERT_EQ(get_token((char **)&command), (void *)0);

  tk = get_token((char **)&command);
  ASSERT_EQ(tk->type, INTEGER);
  ASSERT_EQ(tk->lexeme.integer, 4);

  ASSERT_EQ(get_token((char **)&command)->type, COMMA);

  tk = get_token((char **)&command);
  ASSERT_EQ(tk->type, INTEGER);
  ASSERT_EQ(tk->lexeme.integer, 3);
}

TEST(Tokenizer, ValidRealNumber) {
  const char *command = "0.00000003";
  Token *found = get_token((char **)&command);

  ASSERT_EQ(found->type, REAL);
  ASSERT_EQ(found->lexeme.real, 0.00000003);
}

TEST(Tokenizer, ValidString) {
  const char *command = "\"Hello, World\"";
  Token *found = get_token((char **)&command);

  ASSERT_EQ(found->type, STRING);
  ASSERT_FALSE(!strcmp(found->lexeme.str, "Hello, Worl"));
  ASSERT_TRUE(!strcmp(found->lexeme.str, "Hello, World"));
}

TEST(Tokenizer, InvalidString) {
  const char *command = "\"Hello, World";
  ASSERT_EQ(get_token((char **)&command), (void *)0);
}
