#include "utils.h"

size_t FileSize(FILE *file) {
  size_t size = 0;
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);
  return size;
}

char *ReadFile(const char *filename) {
  FILE *source_file = fopen(filename, "r");
  if (!source_file) return NULL;

  size_t source_file_length = FileSize(source_file);

  char *source = malloc(source_file_length + 1);
  if (!source) return NULL;

  fread(source, sizeof(char), source_file_length, source_file);

  fclose(source_file);
  return source;
}

void PrintAux(int spaces) {
  char *string = malloc(spaces + 1);

  for (size_t i = 0; i < spaces; i++) {
    string[i] = '-';
  }

  printf("%s ", string);

  free(string);

  return string;
}

void RemoveSpaces(char *source) {
  char *i = source;
  char *j = source;
  while(*j != 0)   {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}

void PrintSeparator() {
  printf("\n ========================================================================== \n\n");
}