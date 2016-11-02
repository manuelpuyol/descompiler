#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"
#include "automata.h"

void eval(char* source_code) {
  Lexer lexer = lexer_init(source_code);
  Token* token;

  token = lexer_get_all_tokens(&lexer);

  if(token == NULL) {
    printf("Error na posição %d do arquivo!\n", lexer.cursor);
    exit(-1);
  }

}

int keyword_types_check(Token* token) {
  if(token->type == Keyword) {
    token_print(token);
    return 1;
  }

  return 0;
}

int delimiter_open_braces_check(Token* token) {
  if(token->type == Delimiter) {
    token_print(token);
    return 1;
  }

  return 0;
}

int delimiter_close_braces_check(Token* token) {
  if(token->type == Delimiter) {
    token_print(token);
    return 1;
  }

  return 0;
}

Automata* create_program_automata() {
  Automata* program_automata = automata_init(5);
  Automata* tipos_automata = automata_init(5);
  Automata* assinaturas_automata = automata_init(5);
  Automata* dados_automata = automata_init(5);
  Automata* funcoes_automata = automata_init(3);
  Automata* tipo_automata = automata_init(3);

  // printf("Oiiiii\n");

  Automata* keyword_types_check_automata = automata_transition_init(&keyword_types_check);
  Automata* delimiter_open_braces_check_automata = automata_transition_init(&delimiter_open_braces_check);
  Automata* delimiter_close_braces_check_automata = automata_transition_init(&delimiter_close_braces_check);

  //PROGRAM AUTOMATA
  automata_set_final_state(program_automata, 1);
  automata_set_final_state(program_automata, 2);
  automata_set_final_state(program_automata, 3);
  automata_set_final_state(program_automata, 4);
  automata_add_transition(program_automata, 0, 1, tipos_automata);
  automata_add_transition(program_automata, 0, 2, assinaturas_automata);
  automata_add_transition(program_automata, 0, 3, dados_automata);
  automata_add_transition(program_automata, 0, 4, funcoes_automata);
  automata_add_transition(program_automata, 1, 2, assinaturas_automata);
  automata_add_transition(program_automata, 1, 3, dados_automata);
  automata_add_transition(program_automata, 1, 4, funcoes_automata);
  automata_add_transition(program_automata, 2, 3, dados_automata);
  automata_add_transition(program_automata, 2, 4, funcoes_automata);
  automata_add_transition(program_automata, 3, 4, funcoes_automata);

  //TIPOS AUTOMATA
  automata_set_final_state(tipos_automata, 4);
  automata_add_transition(tipos_automata, 0, 1, keyword_types_check_automata);
  automata_add_transition(tipos_automata, 1, 2, delimiter_open_braces_check_automata);
  automata_add_transition(tipos_automata, 2, 3, tipo_automata);
  automata_add_transition(tipos_automata, 3, 3, tipo_automata);
  automata_add_transition(tipos_automata, 3, 4, delimiter_close_braces_check_automata);

  return program_automata;
}

int main(int argc, char const *argv[]) {
  const char* filename = argv[1];
  char* source_code = read_file(filename);

  Automata* program = create_program_automata();

  if(source_code == NULL) {
    printf("Não foi possível abrir o arquivo %s!\n", filename);
  }
  else {
    // printf("Hello %s\n", source_code);
    eval(source_code);
  }

  return 0;
}
