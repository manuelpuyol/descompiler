#include "token.h"

#define GetTokenSize(token) (token->end - token->ini + 1)

Token *InitToken(enum TokenType type, int ini, int end, char *source_code) {
  Token *token = (Token *)malloc(sizeof(Token));

  token->type = type;
  token->ini = ini;
  token->end = end;
  token->source_code = source_code;

  return token;
}

char *GetTokenValue(Token *token) {
  char *value = (char*)malloc(GetTokenSize(token) + 1);

  strncpy(value, &token->source_code[token->ini], GetTokenSize(token));

  return value;
}

void PrintToken(Token *token, int spaces) {
  if(token->type == Identifier) {
    printf("%sIdentifier: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Keyword) {
    printf("%sKeyword: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Operator) {
    printf("%sOperator: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == String) {
    printf("%sString: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Delimiter) {
    printf("%sDelimiter: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Eof) {
    printf("%sEOF: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else if(token->type == Number) {
    printf("%sNumber: %s %d %d\n", PrintAux(spaces), GetTokenValue(token), token->ini, token->end);
  }
  else {
    printf("Error!\n");
  }
}

int SetTokenKeyword(Token *token) {
  char keywords[][256] = {
    "var", "if", "else", "throw", "true", "false", "unless", "function", "while", "for", "types", "as", "int", "char",
    "bool", "float", "struct", "data", "functions", "return", "main", "print", "println", "prints", "printsln"
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
