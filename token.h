#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string.h>

typedef enum Type { Identifier, Number } Class;

typedef struct Token {
  enum Type type;
  char *ini;
  char *end;
} Token;

int tokenLength(Token *token);

#endif
