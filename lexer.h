#ifndef _LEXER_H_
#define _LEXER_H_

#include "token.h"

typedef struct Lexer {
  char *source_code;
  int cursor;
} Lexer;

Lexer InitLexer(char *);
Token *GetNextToken(Lexer *);
Token *GetAllTokens(Lexer *);

#endif
