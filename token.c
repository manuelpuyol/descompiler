#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define GetTokenSize(token) (token->end - token->ini + 1)

Token *InitToken(enum TokenType type, int ini, int end, char *source_code) {
  Token *token = malloc(sizeof (Token));

  token->type = type;
  token->ini = ini;
  token->end = end;
  token->source_code = source_code;

  return token;
}

char *GetTokenValue(Token *token) {
  char *value = (char*) malloc(sizeof(char) * (GetTokenSize(token) + 1));

  strncpy(value, &token->source_code[token->ini], GetTokenSize(token));

  return value;
}

void PrintToken(Token *token) {
  if(token->type == Identifier) {
    printf("Identifier: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Keyword) {
    printf("Keyword: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Operator) {
    printf("Operator: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == String) {
    printf("String: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Delimiter) {
    printf("Delimiter: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Eof) {
    printf("EOF: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Number) {
    printf("Number: %s %d %d\n", GetTokenValue(token), token->ini, token->end);
  }
  else {
    printf("Error!\n");
  }
}

int SetTokenKeyword(Token *token) {
  char keywords[][256] = {
    "var", "if", "else", "throw", "true", "false", "unless", "function", "while",
    "for", //10
    "types", "as", "int", "char", "bool", "float", "struct", "data", "functions", //19
    "return", "main", "printe", "printeln", "prints", "printsln"
  };
  int keywords_length = 25;
  char *value = GetTokenValue(token);

  for (size_t i = 0; i < keywords_length; i++) {
    if(strcmp(keywords[i], value) == 0) {
      token->type = Keyword;
      return 1;
    }
  }

  return 0;
}
