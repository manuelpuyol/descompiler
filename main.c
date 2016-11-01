#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"

void eval(char* source_code) {
  Lexer lexer = lexer_init(source_code);
  Token* token;

  token = lexer_get_all_tokens(&lexer);

  if(token == NULL) {
    printf("Error na posição %d do arquivo!\n", lexer.cursor);
    exit(-1);
  }

}

int main(int argc, char const *argv[]) {
  const char* filename = argv[1];
  char* source_code = read_file(filename);

  if(source_code == NULL) {
    printf("Não foi possível abrir o arquivo %s!\n", filename);
  }
  else {
    // printf("Hello %s\n", source_code);
    eval(source_code);
  }

  return 0;
}
