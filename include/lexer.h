#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "utils.h"

typedef struct _Lexer {
  char *source_code;
  int cursor;
} Lexer;

Lexer InitLexer(char *);
Token *GetNextToken(Lexer *);
Token *GetAllTokens(Lexer *);

#endif
