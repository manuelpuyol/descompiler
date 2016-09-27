#include "lexer.h"

Lexer lexer_init(char* source_code) {
  Lexer lexer = { source_code, 0 };

  return lexer;
}
