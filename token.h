#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string.h>

typedef enum TokenType { Identifier, Number } Class;

typedef struct Token {
  enum TokenType type;
  int ini;
  int end;
  char* source_code;
} Token;

Token* token_init(enum TokenType type, int ini, int end, char* source_code);
void token_print(Token* token);

#endif
