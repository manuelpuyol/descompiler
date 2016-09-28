#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string.h>

typedef enum TokenType { Identifier, Keyword, Operator, String, Delimiter, Eof } Class;

typedef struct Token {
  enum TokenType type;
  int ini;
  int end;
  char* source_code;
} Token;

Token* token_init(enum TokenType type, int ini, int end, char* source_code);
void token_print(Token* token);
int token_change_if_keyword(Token* token);

#endif
