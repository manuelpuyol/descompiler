#include "token.h"

int GetTokenSize(Token *token) {
  return token->end - token->ini + 1;
}

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
  char *token_str = GetTokenValue(token);
  // char *aux = PrintAux(spaces);

  if(token->type == Identifier) {
    printf("Identifier: %s\n", token_str);
  } else if(token->type == Keyword) {
    printf("Keyword: %s\n", token_str);
  } else if(token->type == Operator) {
    printf("Operator: %s\n", token_str);
  } else if(token->type == String) {
    printf("String: %s\n", token_str);
  } else if(token->type == Delimiter) {
    printf("Delimiter: %s\n", token_str);
  } else if(token->type == Eof) {
    printf("EOF: %s\n", token_str);
  } else if(token->type == Number) {
    printf("Number: %s\n", token_str);
  } else {
    printf("Error!\n");
  }

  // free(aux);
  free(token_str);
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
      free(value);
      token->type = Keyword;

      return 1;
    }
  }
  free(value);

  return 0;
}
