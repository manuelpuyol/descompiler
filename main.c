#include <stdio.h>
#include <string.h>
#include "token.h"

int main(int argc, char const *argv[]) {
  const char *filename = argv[1];
  FILE *sourceCode = fopen(filename, "r");
  Token token = {Number, NULL, NULL};

  printf("%d\n", tokenLength(&token));

  if(sourceCode == NULL) {
    printf("Arquivo %s não encontrado!\n", filename);
  }
  else {
    printf("Hello %s\n", filename);
  }

  return 0;
}
