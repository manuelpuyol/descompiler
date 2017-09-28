#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef enum TokenType { Identifier, Keyword, Operator, String, Delimiter, Eof, Number } TokenType;

typedef struct _Token {
  enum TokenType type;
  int ini, end;
  char* source_code;
  struct Token *next, *prev;
  char *value;
} Token;

Token *InitToken(enum TokenType, int, int, char *);
void PrintToken(Token *, int);
int SetTokenKeyword(Token *);
char *GetTokenValue(Token *);
void FreeTokens(Token *);

#endif
