#ifndef CQL_TOKENIZER_H
#define CQL_TOKENIZER_H

#include "token.h"

Token *get_token(char **);

Token *make_token(TokenType);
Token *make_number_token(u64 *, char *);
Token *make_identifier_token(u64 *, char *);

TokenType typeof_identifier(const char *);
bool compare_lexeme(u8, u8, const char *, const char *);

char advance(u64 *, const char *);
void skip_whitespace(u64 *, const char *);

bool is_digit(char);
bool is_alphabetic(char);
bool is_alphanumeric(char);

char *get_substr(const char *, u64, u64);

#endif
