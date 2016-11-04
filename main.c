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

#define AUTOMATA_OPERATOR(name, symb) int operator_##name ## _check(Token* token) { \
  if(token->type == Operator && !strcmp(token_value(token), symb)) { \
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
AUTOMATA_KEYWORK(data);
AUTOMATA_KEYWORK(functions);
AUTOMATA_KEYWORK(return);
AUTOMATA_KEYWORK(main);

AUTOMATA_DELIMITER(open_braces, "{");
AUTOMATA_DELIMITER(close_braces, "}");
AUTOMATA_DELIMITER(open_parenthesis, "(");
AUTOMATA_DELIMITER(close_parenthesis, ")");
AUTOMATA_DELIMITER(open_brackets, "[");
AUTOMATA_DELIMITER(close_brackets, "]");
AUTOMATA_DELIMITER(semicolon, ";");
AUTOMATA_DELIMITER(comma, ",");

AUTOMATA_OPERATOR(equal, "=");
AUTOMATA_OPERATOR(minus, "-");
AUTOMATA_OPERATOR(plus, "+");
AUTOMATA_OPERATOR(mod, "%");
AUTOMATA_OPERATOR(div, "/");
AUTOMATA_OPERATOR(mult, "*");
AUTOMATA_OPERATOR(dot, ".");

Automata* create_program_automata() {
  AUTOMATA_TRANSITION_INIT(keyword_types_check);
  AUTOMATA_TRANSITION_INIT(keyword_as_check);
  AUTOMATA_TRANSITION_INIT(keyword_char_check);
  AUTOMATA_TRANSITION_INIT(keyword_bool_check);
  AUTOMATA_TRANSITION_INIT(keyword_float_check);
  AUTOMATA_TRANSITION_INIT(keyword_int_check);
  AUTOMATA_TRANSITION_INIT(keyword_struct_check);
  AUTOMATA_TRANSITION_INIT(keyword_data_check);
  AUTOMATA_TRANSITION_INIT(keyword_functions_check);
  AUTOMATA_TRANSITION_INIT(keyword_return_check);
  AUTOMATA_TRANSITION_INIT(keyword_main_check);
  AUTOMATA_TRANSITION_INIT(delimiter_open_braces_check);
  AUTOMATA_TRANSITION_INIT(delimiter_close_braces_check);
  AUTOMATA_TRANSITION_INIT(delimiter_open_parenthesis_check);
  AUTOMATA_TRANSITION_INIT(delimiter_close_parenthesis_check);
  AUTOMATA_TRANSITION_INIT(delimiter_open_brackets_check);
  AUTOMATA_TRANSITION_INIT(delimiter_close_brackets_check);
  AUTOMATA_TRANSITION_INIT(delimiter_semicolon_check);
  AUTOMATA_TRANSITION_INIT(delimiter_comma_check);
  AUTOMATA_TRANSITION_INIT(operator_equal_check);
  AUTOMATA_TRANSITION_INIT(operator_minus_check);
  AUTOMATA_TRANSITION_INIT(operator_plus_check);
  AUTOMATA_TRANSITION_INIT(operator_mod_check);
  AUTOMATA_TRANSITION_INIT(operator_div_check);
  AUTOMATA_TRANSITION_INIT(operator_mult_check);
  AUTOMATA_TRANSITION_INIT(operator_dot_check);
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
  Automata* dados_automata = automata_init(5, "dados"); //OK
  Automata* assinaturas_automata = automata_init(5, "assinaturas"); //OK
  Automata* assinatura_automata = automata_init(7, "assinatura"); //OK
  Automata* parametro_automata = automata_init(3, "parametro"); //OK
  Automata* declaracao_automata = automata_init(7, "declaracao"); //OK
  Automata* comandos_funcao_automata = automata_init(3, "comandos_funcao"); //OK
  Automata* lista_comandos_automata = automata_init(2, "lista_comandos"); //OK
  Automata* comando_automata = automata_init(2, "comando"); //OK
  Automata* atribuicao_automata = automata_init(5, "atribuicao"); //OK
  Automata* expressao_automata = automata_init(2, "expressao"); //OK
  Automata* aritmetica_automata = automata_init(2, "aritmetica"); //OK
  Automata* termo_arita_automata = automata_init(2, "termo_arita"); //OK
  Automata* fator_arit_automata = automata_init(5, "fator_arit"); //OK
  Automata* variavel_automata = automata_init(6, "variavel"); //OK
  Automata* retorno_automata = automata_init(4, "retorno"); //OK
  Automata* main_automata = automata_init(9, "main"); //OK
  Automata* chamada_automata = automata_init(5, "chamada");
  Automata* inteiro_automata = automata_init(5, "inteiro");
  Automata* impressao_automata = automata_init(5, "impressao");
  Automata* leitura_automata = automata_init(5, "leitura");
  Automata* while_automata = automata_init(5, "while");
  Automata* ifelse_automata = automata_init(5, "ifelse");
  Automata* if_automata = automata_init(5, "if");
  Automata* caractere_automata = automata_init(5, "caractere");
  Automata* booleana_automata = automata_init(5, "booleana");
  Automata* numero_automata = automata_init(5, "numero");

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

  //TIPO_NOME AUTOMATA
  automata_set_final_state(tipo_nome_automata, 1);
  automata_add_transition(tipo_nome_automata, 0, 1, nome_automata);
  automata_add_transition(tipo_nome_automata, 0, 1, tipo_base_automata);

  //DADOS AUTOMATA
  automata_set_final_state(dados_automata, 4);
  automata_add_transition(dados_automata, 3, 4, delimiter_close_braces_check_automata);
  automata_add_transition(dados_automata, 3, 3, declaracao_automata);
  automata_add_transition(dados_automata, 2, 3, declaracao_automata);
  automata_add_transition(dados_automata, 1, 2, delimiter_open_braces_check_automata);
  automata_add_transition(dados_automata, 0, 1, keyword_data_check_automata);

  //ASSINATURAS AUTOMATA
  automata_set_final_state(assinaturas_automata, 4);
  automata_add_transition(assinaturas_automata, 3, 4, delimiter_close_braces_check_automata);
  automata_add_transition(assinaturas_automata, 3, 3, assinatura_automata);
  automata_add_transition(assinaturas_automata, 2, 3, assinatura_automata);
  automata_add_transition(assinaturas_automata, 1, 2, delimiter_open_braces_check_automata);
  automata_add_transition(assinaturas_automata, 0, 1, keyword_functions_check_automata);

  //ASSINATURAS AUTOMATA
  automata_set_final_state(assinatura_automata, 6);
  automata_add_transition(assinatura_automata, 5, 6, delimiter_semicolon_check_automata);
  automata_add_transition(assinatura_automata, 4, 5, delimiter_close_parenthesis_check_automata);
  automata_add_transition(assinatura_automata, 4, 3, delimiter_comma_check_automata);
  automata_add_transition(assinatura_automata, 3, 4, parametro_automata);
  automata_add_transition(assinatura_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  automata_add_transition(assinatura_automata, 1, 2, nome_automata);
  automata_add_transition(assinatura_automata, 0, 1, tipo_nome_automata);

  //PARAMETRO AUTOMATA
  automata_set_final_state(parametro_automata, 2);
  automata_add_transition(parametro_automata, 1, 2, nome_automata);
  automata_add_transition(parametro_automata, 0, 1, tipo_nome_automata);

  //DECLARACAO AUTOMATA
  automata_set_final_state(declaracao_automata, 4);
  automata_add_transition(declaracao_automata, 6, 4, delimiter_semicolon_check_automata);
  automata_add_transition(declaracao_automata, 5, 6, delimiter_close_brackets_check_automata);
  automata_add_transition(declaracao_automata, 3, 5, inteiro_automata);
  automata_add_transition(declaracao_automata, 2, 4, delimiter_semicolon_check_automata);
  automata_add_transition(declaracao_automata, 2, 3, delimiter_open_brackets_check_automata);
  automata_add_transition(declaracao_automata, 1, 2, nome_automata);
  automata_add_transition(declaracao_automata, 0, 1, tipo_nome_automata);

  //COMANDOS_FUNCAO AUTOMATA
  automata_set_final_state(comandos_funcao_automata, 2);
  automata_add_transition(comandos_funcao_automata, 1, 2, retorno_automata);
  automata_add_transition(comandos_funcao_automata, 0, 1, lista_comandos_automata);

  //LISTA_COMANDOS AUTOMATA
  automata_set_final_state(lista_comandos_automata, 1);
  automata_add_transition(lista_comandos_automata, 1, 1, comando_automata);
  automata_add_transition(lista_comandos_automata, 0, 1, comando_automata);

  //COMANDO AUTOMATA
  automata_set_final_state(comando_automata, 1);
  automata_add_transition(comando_automata, 0, 1, impressao_automata);
  automata_add_transition(comando_automata, 0, 1, leitura_automata);
  automata_add_transition(comando_automata, 0, 1, while_automata);
  automata_add_transition(comando_automata, 0, 1, ifelse_automata);
  automata_add_transition(comando_automata, 0, 1, if_automata);
  automata_add_transition(comando_automata, 0, 1, atribuicao_automata);

  //ATRIBUICAO AUTOMATA
  automata_set_final_state(atribuicao_automata, 4);
  automata_add_transition(atribuicao_automata, 3, 4, delimiter_semicolon_check_automata);
  automata_add_transition(atribuicao_automata, 2, 3, caractere_automata);
  automata_add_transition(atribuicao_automata, 2, 3, expressao_automata);
  automata_add_transition(atribuicao_automata, 1, 2, operator_equal_check_automata);
  automata_add_transition(atribuicao_automata, 0, 1, nome_automata);

  //EXPRESSAO AUTOMATA
  automata_set_final_state(expressao_automata, 1);
  automata_add_transition(expressao_automata, 0, 1, booleana_automata);
  automata_add_transition(expressao_automata, 0, 1, aritmetica_automata);

  //ARITIMETICA AUTOMATA
  automata_set_final_state(aritmetica_automata, 1);
  automata_add_transition(aritmetica_automata, 1, 0, operator_minus_check_automata);
  automata_add_transition(aritmetica_automata, 1, 0, operator_plus_check_automata);
  automata_add_transition(aritmetica_automata, 0, 1, termo_arita_automata);

  //TERMO_ARITA AUTOMATA
  automata_set_final_state(termo_arita_automata, 1);
  automata_add_transition(termo_arita_automata, 1, 0, operator_mod_check_automata);
  automata_add_transition(termo_arita_automata, 1, 0, operator_div_check_automata);
  automata_add_transition(termo_arita_automata, 1, 0, operator_mult_check_automata);
  automata_add_transition(termo_arita_automata, 0, 1, fator_arit_automata);

  //FATOR_ARIT AUTOMATA
  automata_set_final_state(fator_arit_automata, 1);
  automata_add_transition(fator_arit_automata, 4, 1, delimiter_close_parenthesis_check_automata);
  automata_add_transition(fator_arit_automata, 3, 4, aritmetica_automata);
  automata_add_transition(fator_arit_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  automata_add_transition(fator_arit_automata, 2, 1, numero_automata);
  automata_add_transition(fator_arit_automata, 0, 1, chamada_automata);
  automata_add_transition(fator_arit_automata, 0, 1, variavel_automata);
  automata_add_transition(fator_arit_automata, 0, 3, delimiter_open_parenthesis_check_automata);
  automata_add_transition(fator_arit_automata, 0, 2, operator_minus_check_automata);
  automata_add_transition(fator_arit_automata, 0, 1, numero_automata);

  //VARIAVEL AUTOMATA
  automata_set_final_state(variavel_automata, 1);
  automata_set_final_state(variavel_automata, 5);
  automata_add_transition(variavel_automata, 4, 5, delimiter_close_brackets_check_automata);
  automata_add_transition(variavel_automata, 3, 5, nome_automata);
  automata_add_transition(variavel_automata, 2, 4, inteiro_automata);
  automata_add_transition(variavel_automata, 1, 3, operator_dot_check_automata);
  automata_add_transition(variavel_automata, 1, 2, delimiter_open_brackets_check_automata);
  automata_add_transition(variavel_automata, 0, 1, nome_automata);

  //RETORNO AUTOMATA
  automata_set_final_state(retorno_automata, 3);
  automata_add_transition(retorno_automata, 2, 3, delimiter_semicolon_check_automata);
  automata_add_transition(retorno_automata, 1, 2, expressao_automata);
  automata_add_transition(retorno_automata, 0, 1, keyword_return_check_automata);

  //MAIN AUTOMATA
  automata_set_final_state(main_automata, 8);
  automata_add_transition(main_automata, 7, 8, delimiter_close_braces_check_automata);
  automata_add_transition(main_automata, 6, 7, comandos_funcao_automata);
  automata_add_transition(main_automata, 5, 6, dados_automata);
  automata_add_transition(main_automata, 4, 5, delimiter_open_braces_check_automata);
  automata_add_transition(main_automata, 3, 4, delimiter_close_parenthesis_check_automata);
  automata_add_transition(main_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  automata_add_transition(main_automata, 1, 2, keyword_main_check_automata);
  automata_add_transition(main_automata, 0, 1, keyword_int_check_automata);

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
