#ifndef _LEXER_H_
#define _LEXER_H_

#include "token.h"

typedef struct Lexer {
  char *source_code;
  int cursor;
} Lexer;

Lexer lexer_init(char* source_code);
Token* lexer_get_next_token(Lexer* lexer);
Token* lexer_get_all_tokens(Lexer* lexer);

#endif
