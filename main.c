#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char const *argv[]) {
  const char* filename = argv[1];
  char* source_code = read_file(filename);

  if(source_code == NULL) {
    printf("Não foi possível abrir o arquivo %s!\n", filename);
  }
  else {
    printf("Hello %s\n", source_code);
  }

  return 0;
}
