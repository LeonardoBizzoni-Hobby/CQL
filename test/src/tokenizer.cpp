#include <gtest/gtest.h>

extern "C" {
  #include <string.h>

  #include "statements/tokenizer.h"
  #include "statements/token_type.h"
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

TEST(Tokenizer, SimpleTokenSequence) {
  const char *command = "(,)";

  ASSERT_EQ(get_token((char **)&command)->type, LEFT_PAREN);
  ASSERT_EQ(get_token((char **)&command)->type, COMMA);
  ASSERT_EQ(get_token((char **)&command)->type, RIGHT_PAREN);
  ASSERT_EQ(get_token((char **)&command), (void *)0);
}
