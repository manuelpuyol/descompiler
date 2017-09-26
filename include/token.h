#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string.h>

typedef enum TokenType { Identifier, Keyword, Operator, String, Delimiter, Eof, Number } TokenType;

typedef struct _Token {
  enum TokenType type;
  int ini;
  int end;
  char* source_code;
  struct Token *next;
  struct Token *prev;
} Token;

Token *InitToken(enum TokenType, int, int, char *);
void PrintToken(Token *);
int SetTokenKeyword(Token *);
char *GetTokenValue(Token *);

#endif
