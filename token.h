#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string.h>

typedef enum TokenType { Identifier, Keyword, Operator, String, Delimiter, Eof, Number } TokenType;

typedef struct Token {
  enum TokenType type;
  int ini;
  int end;
  char* source_code;
  struct Token* next;
  struct Token* prev;
} Token;

Token* token_init(enum TokenType type, int ini, int end, char* source_code);
void token_print(Token* token);
int token_change_if_keyword(Token* token);
char* token_value(Token* token);

#endif
