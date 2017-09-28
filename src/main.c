#include "utils.h"
#include "lexer.h"
#include "token.h"

void eval(char *source_code) {
  // RemoveSpaces(source_code);
  Lexer lexer = InitLexer(source_code);
  Token *token;

  token = GetAllTokens(&lexer);

  if(token == NULL) {
    printf("Error na posição %d do arquivo!\n", lexer.cursor);
    exit(-1);
  }

  FreeTokens(token);
}

int main(int argc, char const *argv[]) {
  const char *filename = argv[1];
  char *source_code = ReadFile(filename);

  if(source_code == NULL) {
    printf("Não foi possível abrir o arquivo %s!\n", filename);
  }
  else {
    eval(source_code);
  }

  free(source_code);

  return 0;
}
