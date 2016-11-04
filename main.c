#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "lexer.h"
#include "token.h"
#include "automata.h"

#define AUTOMATA_KEYWORK(name) int keyword_##name ## _check(Token* token) { \
  if(token->type == Keyword && !strcmp(token_value(token), #name)) { \
    token_print(token); \
    return 1; \
  } \
\
  return 0; \
}

#define AUTOMATA_DELIMITER(name, symb) int delimiter_##name ## _check(Token* token) { \
  if(token->type == Delimiter && !strcmp(token_value(token), symb)) { \
    token_print(token); \
    return 1; \
  } \
\
  return 0; \
}

int identifier_check(Token* token) {
  if(token->type == Identifier) {
    token_print(token);
    return 1;
  }
  return 0;
}

#define AUTOMATA_TRANSITION_INIT(name) Automata* name ## _automata = automata_transition_init(&name, #name)

AUTOMATA_KEYWORK(types);
AUTOMATA_KEYWORK(char);
AUTOMATA_KEYWORK(bool);
AUTOMATA_KEYWORK(float);
AUTOMATA_KEYWORK(int);
AUTOMATA_KEYWORK(as);
AUTOMATA_KEYWORK(struct);

AUTOMATA_DELIMITER(open_braces, "{");
AUTOMATA_DELIMITER(close_braces, "}");
AUTOMATA_DELIMITER(open_parenthesis, ")");
AUTOMATA_DELIMITER(close_parenthesis, "(");
AUTOMATA_DELIMITER(semicolon, ";");
AUTOMATA_DELIMITER(comma, ",");

Automata* create_program_automata() {
  AUTOMATA_TRANSITION_INIT(keyword_types_check);
  AUTOMATA_TRANSITION_INIT(keyword_as_check);
  AUTOMATA_TRANSITION_INIT(keyword_char_check);
  AUTOMATA_TRANSITION_INIT(keyword_bool_check);
  AUTOMATA_TRANSITION_INIT(keyword_float_check);
  AUTOMATA_TRANSITION_INIT(keyword_int_check);
  AUTOMATA_TRANSITION_INIT(keyword_struct_check);
  AUTOMATA_TRANSITION_INIT(delimiter_open_braces_check);
  AUTOMATA_TRANSITION_INIT(delimiter_close_braces_check);
  AUTOMATA_TRANSITION_INIT(delimiter_open_parenthesis_check);
  AUTOMATA_TRANSITION_INIT(delimiter_close_parenthesis_check);
  AUTOMATA_TRANSITION_INIT(delimiter_semicolon_check);
  AUTOMATA_TRANSITION_INIT(delimiter_comma_check);
  AUTOMATA_TRANSITION_INIT(identifier_check);

  Automata* program_automata = automata_init(5, "program"); //OK
  Automata* tipos_automata = automata_init(5, "tipos"); //OK
  Automata* tipo_automata = automata_init(2, "tipo"); //OK
  Automata* renomear_automata = automata_init(5, "renomear"); //OK
  Automata* estrutura_automata = automata_init(7, "estrutura"); //OK
  Automata* nome_automata = identifier_check_automata; //OK
  Automata* tipo_base_automata = automata_init(2, "tipo_base"); //OK
  Automata* funcoes_automata = automata_init(3, "funcoes"); //OK
  Automata* implementacao_automata = automata_init(10, "implementacao"); //OK
  Automata* tipo_nome_automata = automata_init(2, "tipo_nome"); //OK
  Automata* declaracao_automata = automata_init(2, "declaracao");
  Automata* assinaturas_automata = automata_init(5, "assinaturas");
  Automata* dados_automata = automata_init(5, "dados");
  Automata* main_automata = automata_init(5, "main");
  Automata* comandos_funcao_automata = automata_init(5, "comandos_funcao");
  Automata* parametro_automata = automata_init(5, "parametro");

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
  automata_set_final_state(renomear_automata, 4);
  automata_add_transition(renomear_automata, 3, 4, delimiter_semicolon_check_automata);
  automata_add_transition(renomear_automata, 2, 3, nome_automata);
  automata_add_transition(renomear_automata, 1, 2, keyword_as_check_automata);
  automata_add_transition(renomear_automata, 0, 1, tipo_base_automata);

  //TIPO_BASE AUTOMATA
  automata_set_final_state(tipo_base_automata, 1);
  automata_add_transition(tipo_base_automata, 0, 1, keyword_char_check_automata);
  automata_add_transition(tipo_base_automata, 0, 1, keyword_bool_check_automata);
  automata_add_transition(tipo_base_automata, 0, 1, keyword_float_check_automata);
  automata_add_transition(tipo_base_automata, 0, 1, keyword_int_check_automata);

  //ESTRUTURA AUTOMATA
  automata_set_final_state(estrutura_automata, 6);
  automata_add_transition(estrutura_automata, 5, 6, delimiter_semicolon_check_automata);
  automata_add_transition(estrutura_automata, 4, 5, delimiter_close_braces_check_automata);
  automata_add_transition(estrutura_automata, 4, 4, declaracao_automata);
  automata_add_transition(estrutura_automata, 3, 4, declaracao_automata);
  automata_add_transition(estrutura_automata, 2, 3, delimiter_open_braces_check_automata);
  automata_add_transition(estrutura_automata, 1, 2, nome_automata);
  automata_add_transition(estrutura_automata, 0, 1, keyword_struct_check_automata);

  //FUNCOES AUTOMATA
  automata_set_final_state(funcoes_automata, 2);
  automata_add_transition(funcoes_automata, 1, 2, main_automata);
  automata_add_transition(funcoes_automata, 1, 1, implementacao_automata);
  automata_add_transition(funcoes_automata, 0, 1, implementacao_automata);

  //IMPLEMENTACAO AUTOMATA
  automata_set_final_state(implementacao_automata, 9);
  automata_add_transition(implementacao_automata, 8, 9, delimiter_close_braces_check_automata);
  automata_add_transition(implementacao_automata, 7, 8, comandos_funcao_automata);
  automata_add_transition(implementacao_automata, 6, 7, dados_automata);
  automata_add_transition(implementacao_automata, 5, 6, delimiter_open_braces_check_automata);
  automata_add_transition(implementacao_automata, 4, 5, delimiter_close_parenthesis_check_automata);
  automata_add_transition(implementacao_automata, 4, 3, delimiter_comma_check_automata);
  automata_add_transition(implementacao_automata, 3, 4, parametro_automata);
  automata_add_transition(implementacao_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  automata_add_transition(implementacao_automata, 1, 2, nome_automata);
  automata_add_transition(implementacao_automata, 0, 1, tipo_nome_automata);

  //TIPO_NOME
  automata_set_final_state(tipo_nome_automata, 1);
  automata_add_transition(tipo_nome_automata, 0, 1, nome_automata);
  automata_add_transition(tipo_nome_automata, 0, 1, tipo_base_automata);

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
