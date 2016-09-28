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

Token* lexer_extract_keyword_or_identifier(Lexer* lexer) {
  Token* token = NULL;
  char c = lexer_peek_char(lexer);

  if(!isalpha(c)) {
    return NULL;
  }

  token = token_init(Identifier, lexer->cursor, -1, lexer->source_code);

  do {
    c = lexer_next_char(lexer);
  } while(isalpha(c) || isdigit(c));

  lexer_prev_char(lexer);
  token->end = lexer->cursor - 1;

  token_change_if_keyword(token);

  return token;
}

Token* lexer_extract_operator(Lexer* lexer) {
  Token* token = NULL;
  int cursor_ini = lexer->cursor;
  char c = lexer_next_char(lexer);

  switch (c) {
    case '=':
      token = token_init(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = lexer_peek_char(lexer);
      switch (c) {
        case '=':
          token->end++;
          lexer_next_char(lexer);
      }
      break;
    default:
      lexer_prev_char(lexer);
  }

  return token;
}

Token* lexer_extract_delimiter(Lexer* lexer) {
  Token* token = NULL;
  int cursor_ini = lexer->cursor;
  char c = lexer_next_char(lexer);

  switch (c) {
    case ';':
      return token_init(Delimiter, cursor_ini, cursor_ini, lexer->source_code);
    default:
      lexer_prev_char(lexer);
  }

  return token;
}

Token* lexer_extract_eof(Lexer* lexer) {
  int cursor_ini = lexer->cursor;
  char c = lexer_next_char(lexer);

  if(c == '\0') {
    return token_init(Eof, cursor_ini, cursor_ini, lexer->source_code);
  }

  lexer_prev_char(lexer);
  return NULL;
}

Token* lexer_extract_string(Lexer* lexer) {
  Token* token = NULL;
  char string_start = lexer_peek_char(lexer);
  char c = string_start;

  if(c != '"' && c != '\'') {
    return NULL;
  }

  token = token_init(String, lexer->cursor, -1, lexer->source_code);

  c = lexer_next_char(lexer);
  do {
    c = lexer_next_char(lexer);
  } while(c != string_start);

  token->end = lexer->cursor - 1;

  return token;
}

Token* lexer_get_next_token(Lexer* lexer) {
  Token* token = NULL;

  lexer_skip_white_spaces(lexer);

  if((token = lexer_extract_eof(lexer))) {
    return token;
  }
  if((token = lexer_extract_keyword_or_identifier(lexer))) {
    return token;
  }
  if((token = lexer_extract_operator(lexer))) {
    return token;
  }
  if((token = lexer_extract_string(lexer))) {
    return token;
  }
  if((token = lexer_extract_delimiter(lexer))) {
    return token;
  }

  return token;
}
