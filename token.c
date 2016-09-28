#include <stdio.h>
#include "token.h"

#define token_size(token) (token->end - token->ini + 1)

Token* token_init(enum TokenType type, int ini, int end, char* source_code) {
  Token* token = malloc(sizeof (Token));

  token->type = type;
  token->ini = ini;
  token->end = end;
  token->source_code = source_code;

  return token;
}

char* token_value(Token* token) {
  char* value = (char*) malloc(sizeof(char) * (token_size(token) + 1));

  strncpy(value, &token->source_code[token->ini], token_size(token));

  return value;
}


void token_print(Token* token) {
  if(token->type == Identifier) {
    printf("Identifier: %s %d %d\n", token->ini, token->end, token_value(token));
  }
  else {
    printf("Error!\n");
  }
}
