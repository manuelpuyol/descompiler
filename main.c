#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"
#include "automata.h"

int keyword_types_check(Token* token) {
  if(token->type == Keyword) {
    token_print(token);
    return 1;
  }

  return 0;
}

int keyword_as_check(Token* token) {
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

int delimiter_semicolon_check(Token* token) {
  if(token->type == Delimiter) {
    token_print(token);
    return 1;
  }

  return 0;
}

Automata* create_program_automata() {
  Automata* program_automata = automata_init(5, "program"); //OK
  Automata* tipos_automata = automata_init(5, "tipos"); //OK
  Automata* assinaturas_automata = automata_init(5, "assinaturas");
  Automata* dados_automata = automata_init(5, "dados");
  Automata* funcoes_automata = automata_init(3, "funcoes");
  Automata* tipo_automata = automata_init(2, "tipo"); //OK
  Automata* renomear_automata = automata_init(5, "renomear"); //OK
  Automata* estrutura_automata = automata_init(2, "estrutura");
  Automata* nome_automata = automata_init(2, "nome");
  Automata* tipo_base_automata = automata_init(2, "tipo_base");

  Automata* keyword_types_check_automata = automata_transition_init(&keyword_types_check, "keyword_types_check");
  Automata* keyword_as_check_automata = automata_transition_init(&keyword_as_check, "keyword_as_check");
  Automata* delimiter_open_braces_check_automata = automata_transition_init(&delimiter_open_braces_check, "delimiter_open_braces_check");
  Automata* delimiter_close_braces_check_automata = automata_transition_init(&delimiter_close_braces_check, "delimiter_close_braces_check");
  Automata* delimiter_semicolon_check_automata = automata_transition_init(&delimiter_semicolon_check, "delimiter_semicolon_check");

  //PROGRAM AUTOMATA
  automata_set_final_state(program_automata, 1);
  automata_set_final_state(program_automata, 2);
  automata_set_final_state(program_automata, 3);
  automata_set_final_state(program_automata, 4);
  automata_add_transition(program_automata, 0, 2, assinaturas_automata);
  automata_add_transition(program_automata, 0, 3, dados_automata);
  automata_add_transition(program_automata, 0, 4, funcoes_automata);
  automata_add_transition(program_automata, 1, 2, assinaturas_automata);
  automata_add_transition(program_automata, 1, 3, dados_automata);
  automata_add_transition(program_automata, 1, 4, funcoes_automata);
  automata_add_transition(program_automata, 2, 3, dados_automata);
  automata_add_transition(program_automata, 2, 4, funcoes_automata);
  automata_add_transition(program_automata, 3, 4, funcoes_automata);
  automata_add_transition(program_automata, 0, 1, tipos_automata);


  //TIPOS AUTOMATA
  automata_set_final_state(tipos_automata, 4);
  automata_add_transition(tipos_automata, 3, 4, delimiter_close_braces_check_automata);
  automata_add_transition(tipos_automata, 3, 3, tipo_automata);
  automata_add_transition(tipos_automata, 2, 3, tipo_automata);
  automata_add_transition(tipos_automata, 1, 2, delimiter_open_braces_check_automata);
  automata_add_transition(tipos_automata, 0, 1, keyword_types_check_automata);

  //TIPO AUTOMATA
  automata_set_final_state(tipo_automata, 1);
  automata_add_transition(tipo_automata, 0, 1, estrutura_automata);
  automata_add_transition(tipo_automata, 0, 1, renomear_automata);

  //RENOMEAR AUTOMATA
  automata_set_final_state(renomear_automata, 1);
  automata_add_transition(renomear_automata, 3, 4, delimiter_semicolon_check_automata);
  automata_add_transition(renomear_automata, 2, 3, nome_automata);
  automata_add_transition(renomear_automata, 1, 2, keyword_as_check_automata);
  automata_add_transition(renomear_automata, 0, 1, tipo_base_automata);

  return program_automata;
}

void eval(char* source_code) {
  Lexer lexer = lexer_init(source_code);
  Token* token;

  Automata* program = create_program_automata();
  token = lexer_get_all_tokens(&lexer);

  if(token == NULL) {
    printf("Error na posição %d do arquivo!\n", lexer.cursor);
    exit(-1);
  }

  token = automata_apply(program, token, 0);
  if(token == NULL) {
    printf("Não foi possivel compilar o arquivo!\n");
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
