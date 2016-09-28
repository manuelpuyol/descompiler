#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

Lexer lexer_init(char* source_code) {
  Lexer lexer = { source_code, 0 };

  return lexer;
}

char lexer_next_char(Lexer* lexer) {
  return lexer->source_code[lexer->cursor++];
}

char lexer_prev_char(Lexer* lexer) {
  return lexer->source_code[--lexer->cursor];
}

char lexer_peek_char(Lexer* lexer) {
  return lexer->source_code[lexer->cursor];
}

void lexer_skip_white_spaces(Lexer* lexer) {
  while(isspace(lexer_next_char(lexer)));
  lexer_prev_char(lexer);
}

Token* lexer_extract_identifier(Lexer* lexer) {
  Token* token;
  char c = lexer_peek_char(lexer);

  if(!isalpha(c)) {
    return NULL;
  }

  token = token_init(Identifier, lexer->cursor, -1, lexer->source_code);

  do {
    c = lexer_next_char(lexer);
  } while(isalpha(c) || isdigit(c));

  token->end = lexer->cursor - 1;

  return token;
}

Token* lexer_get_next_token(Lexer* lexer) {
  Token* token = NULL;

  lexer_skip_white_spaces(lexer);

  if((token = lexer_extract_identifier(lexer))) {
    return token;
  }

  return token;
}
