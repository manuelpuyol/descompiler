#include <stdlib.h>
#include <stdio.h>
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