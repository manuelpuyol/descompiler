#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

Lexer InitLexer(char *source_code) {
  Lexer lexer = { source_code, 0 };

  return lexer;
}

char GetNextChar(Lexer *lexer) {
  return lexer->source_code[lexer->cursor++];
}

char GetPreviousChar(Lexer *lexer) {
  return lexer->source_code[--lexer->cursor];
}

char GetPeekChar(Lexer *lexer) {
  return lexer->source_code[lexer->cursor];
}

void SkipWhiteSpaces(Lexer *lexer) {
  while(isspace(GetNextChar(lexer)));
  GetPreviousChar(lexer);
}

Token *ExtractKeywordOrIdentifier(Lexer *lexer) {
  Token *token = NULL;
  char c = GetPeekChar(lexer);

  if(!isalpha(c)) {
    return NULL;
  }

  token = InitToken(Identifier, lexer->cursor, -1, lexer->source_code);

  do {
    c = GetNextChar(lexer);
  } while(isalpha(c) || isdigit(c));

  GetPreviousChar(lexer);
  token->end = lexer->cursor - 1;

  SetTokenKeyword(token);

  return token;
}

Token *ExtractNumber(Lexer *lexer) {
  Token *token = NULL;
  char c = GetPeekChar(lexer);

  if(!isdigit(c)) {
    return NULL;
  }

  token = InitToken(Number, lexer->cursor, -1, lexer->source_code);

  do {
    c = GetNextChar(lexer);
  } while(isdigit(c));

  if(c == '.') {
    do {
      c = GetNextChar(lexer);
    } while(isdigit(c));
  }

  GetPreviousChar(lexer);
  token->end = lexer->cursor - 1;

  SetTokenKeyword(token);

  return token;
}

Token *ExtractOperator(Lexer *lexer) {
  Token *token = NULL;
  int cursor_ini = lexer->cursor;
  char c = GetNextChar(lexer);

  switch (c) {
    case '=':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '+':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '+': case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '-':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '-': case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '*':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '*': case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '/':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '>': case '<':
      token = InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
      c = GetPeekChar(lexer);
      switch (c) {
        case '=':
          token->end++;
          GetNextChar(lexer);
      }
      break;
    case '.':
      return InitToken(Operator, cursor_ini, cursor_ini, lexer->source_code);
    default:
      GetPreviousChar(lexer);
  }

  return token;
}

Token *ExtractDelimiter(Lexer *lexer) {
  Token *token = NULL;
  int cursor_ini = lexer->cursor;
  char c = GetNextChar(lexer);

  switch (c) {
    case ';': case '(': case ')': case '{': case '}': case ',': case '[': case ']':
      return InitToken(Delimiter, cursor_ini, cursor_ini, lexer->source_code);
    default:
      GetPreviousChar(lexer);
  }

  return token;
}

Token *ExtractEOF(Lexer *lexer) {
  int cursor_ini = lexer->cursor;
  char c = GetNextChar(lexer);

  if(c == '\0') {
    return InitToken(Eof, cursor_ini, cursor_ini, lexer->source_code);
  }

  GetPreviousChar(lexer);
  return NULL;
}

Token *ExtractString(Lexer *lexer) {
  Token *token = NULL;
  char string_start = GetPeekChar(lexer);
  char c = string_start;

  if(c != '"' && c != '\'') {
    return NULL;
  }

  token = InitToken(String, lexer->cursor, -1, lexer->source_code);

  c = GetNextChar(lexer);
  do {
    c = GetNextChar(lexer);
  } while(c != string_start);

  token->end = lexer->cursor - 1;

  return token;
}

Token *GetNextToken(Lexer *lexer) {
  Token *token = NULL;

  SkipWhiteSpaces(lexer);

  if((token = ExtractEOF(lexer))) {
    return token;
  }
  if((token = ExtractKeywordOrIdentifier(lexer))) {
    return token;
  }
  if((token = ExtractNumber(lexer))) {
    return token;
  }
  if((token = ExtractOperator(lexer))) {
    return token;
  }
  if((token = ExtractString(lexer))) {
    return token;
  }
  if((token = ExtractDelimiter(lexer))) {
    return token;
  }

  return token;
}

Token *GetAllTokens(Lexer *lexer) {
  Token *current_token = NULL, *prev_token = NULL, *first_token = NULL;

  do {
    current_token = GetNextToken(lexer);
    if(current_token != NULL) {
      PrintToken(current_token);

      if(first_token == NULL) {
        first_token = current_token;
      }

      if(prev_token != NULL) {
        current_token->prev = prev_token;
        prev_token->next = current_token;
      }
      prev_token = current_token;
    }
    else {
      return NULL;
    }
  } while(current_token->type != Eof);

  return first_token;
}
