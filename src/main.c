#include "utils.h"
#include "lexer.h"
#include "token.h"
#include "automata.h"


#define AUTOMATA_KEYWORK(name) int keyword_##name ## _check(Token* token, int spaces) { \
  if(token->type == Keyword && !strcmp(GetTokenValue(token), #name)) { \
    PrintToken(token, spaces); \
    return 1; \
  } \
\
  return 0; \
}

#define AUTOMATA_DELIMITER(name, symb) int delimiter_##name ## _check(Token* token, int spaces) { \
  if(token->type == Delimiter && !strcmp(GetTokenValue(token), symb)) { \
    PrintToken(token, spaces); \
    return 1; \
  } \
\
  return 0; \
}

#define AUTOMATA_OPERATOR(name, symb) int operator_##name ## _check(Token* token, int spaces) { \
  if(token->type == Operator && !strcmp(GetTokenValue(token), symb)) { \
    PrintToken(token, spaces); \
    return 1; \
  } \
\
  return 0; \
}

int identifier_check(Token* token, int spaces) {
  if(token->type == Identifier) {
    PrintToken(token, spaces);
    return 1;
  }
  return 0;
}

int number_check(Token* token, int spaces) {
  if(token->type == Number) {
    PrintToken(token, spaces);
    return 1;
  }
  return 0;
}

#define AUTOMATA_TRANSITION_INIT(name) Automata *name ## _automata = InitAutomataTransition(&name, #name)

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
AUTOMATA_KEYWORK(print);
AUTOMATA_KEYWORK(println);
AUTOMATA_KEYWORK(prints);
AUTOMATA_KEYWORK(printsln);

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

Automata *CreateProgramAutomata() {
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
  AUTOMATA_TRANSITION_INIT(keyword_print_check);
  AUTOMATA_TRANSITION_INIT(keyword_println_check);
  AUTOMATA_TRANSITION_INIT(keyword_prints_check);
  AUTOMATA_TRANSITION_INIT(keyword_printsln_check);
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
  AUTOMATA_TRANSITION_INIT(number_check);

  Automata *program_automata = InitAutomata(5, "program"); //OK
  Automata *tipos_automata = InitAutomata(5, "tipos"); //OK
  Automata *tipo_automata = InitAutomata(2, "tipo"); //OK
  Automata *renomear_automata = InitAutomata(5, "renomear"); //OK
  Automata *estrutura_automata = InitAutomata(7, "estrutura"); //OK
  Automata *nome_automata = identifier_check_automata; //OK
  Automata *numero_automata = number_check_automata; //OK
  Automata *tipo_base_automata = InitAutomata(2, "tipo_base"); //OK
  Automata *funcoes_automata = InitAutomata(3, "funcoes"); //OK
  Automata *implementacao_automata = InitAutomata(10, "implementacao"); //OK
  Automata *tipo_nome_automata = InitAutomata(2, "tipo_nome"); //OK
  Automata *dados_automata = InitAutomata(5, "dados"); //OK
  Automata *assinaturas_automata = InitAutomata(5, "assinaturas"); //OK
  Automata *assinatura_automata = InitAutomata(7, "assinatura"); //OK
  Automata *parametro_automata = InitAutomata(3, "parametro"); //OK
  Automata *declaracao_automata = InitAutomata(7, "declaracao"); //OK
  Automata *comandos_funcao_automata = InitAutomata(3, "comandos_funcao"); //OK
  Automata *lista_comandos_automata = InitAutomata(2, "lista_comandos"); //OK
  Automata *comando_automata = InitAutomata(2, "comando"); //OK
  Automata *atribuicao_automata = InitAutomata(5, "atribuicao"); //OK
  Automata *expressao_automata = InitAutomata(2, "expressao"); //OK
  Automata *aritmetica_automata = InitAutomata(2, "aritmetica"); //OK
  Automata *termo_arita_automata = InitAutomata(2, "termo_arita"); //OK
  Automata *fator_arit_automata = InitAutomata(5, "fator_arit"); //OK
  Automata *variavel_automata = InitAutomata(6, "variavel"); //OK
  Automata *retorno_automata = InitAutomata(4, "retorno"); //OK
  Automata *main_automata = InitAutomata(9, "main"); //OK
  Automata *chamada_automata = InitAutomata(5, "chamada"); //OK
  Automata *lista_argumentos_automata = InitAutomata(2, "lista_argumentos"); //OK
  Automata *argumento_automata = InitAutomata(2, "argumento"); //OK
  Automata *impressao_automata = InitAutomata(7, "impressao"); //OK
  Automata *inteiro_automata = InitAutomata(5, "inteiro");
  Automata *leitura_automata = InitAutomata(5, "leitura");
  Automata *while_automata = InitAutomata(5, "while");
  Automata *ifelse_automata = InitAutomata(5, "ifelse");
  Automata *if_automata = InitAutomata(5, "if");
  Automata *caractere_automata = InitAutomata(5, "caractere");
  Automata *booleana_automata = InitAutomata(5, "booleana");
  Automata *string_automata = InitAutomata(5, "string");

  //PROGRAM AUTOMATA
  SetAutomataFinalState(program_automata, 1);
  SetAutomataFinalState(program_automata, 2);
  SetAutomataFinalState(program_automata, 3);
  SetAutomataFinalState(program_automata, 4);
  AddAutomataTransition(program_automata, 0, 2, assinaturas_automata);
  AddAutomataTransition(program_automata, 0, 3, dados_automata);
  AddAutomataTransition(program_automata, 0, 4, funcoes_automata);
  AddAutomataTransition(program_automata, 1, 2, assinaturas_automata);
  AddAutomataTransition(program_automata, 1, 3, dados_automata);
  AddAutomataTransition(program_automata, 1, 4, funcoes_automata);
  AddAutomataTransition(program_automata, 2, 3, dados_automata);
  AddAutomataTransition(program_automata, 2, 4, funcoes_automata);
  AddAutomataTransition(program_automata, 3, 4, funcoes_automata);
  AddAutomataTransition(program_automata, 0, 1, tipos_automata);

  //TIPOS AUTOMATA
  SetAutomataFinalState(tipos_automata, 4);
  AddAutomataTransition(tipos_automata, 3, 4, delimiter_close_braces_check_automata);
  AddAutomataTransition(tipos_automata, 3, 3, tipo_automata);
  AddAutomataTransition(tipos_automata, 2, 3, tipo_automata);
  AddAutomataTransition(tipos_automata, 1, 2, delimiter_open_braces_check_automata);
  AddAutomataTransition(tipos_automata, 0, 1, keyword_types_check_automata);

  //TIPO AUTOMATA
  SetAutomataFinalState(tipo_automata, 1);
  AddAutomataTransition(tipo_automata, 0, 1, estrutura_automata);
  AddAutomataTransition(tipo_automata, 0, 1, renomear_automata);

  //RENOMEAR AUTOMATA
  SetAutomataFinalState(renomear_automata, 4);
  AddAutomataTransition(renomear_automata, 3, 4, delimiter_semicolon_check_automata);
  AddAutomataTransition(renomear_automata, 2, 3, nome_automata);
  AddAutomataTransition(renomear_automata, 1, 2, keyword_as_check_automata);
  AddAutomataTransition(renomear_automata, 0, 1, tipo_base_automata);

  //TIPO_BASE AUTOMATA
  SetAutomataFinalState(tipo_base_automata, 1);
  AddAutomataTransition(tipo_base_automata, 0, 1, keyword_char_check_automata);
  AddAutomataTransition(tipo_base_automata, 0, 1, keyword_bool_check_automata);
  AddAutomataTransition(tipo_base_automata, 0, 1, keyword_float_check_automata);
  AddAutomataTransition(tipo_base_automata, 0, 1, keyword_int_check_automata);

  //ESTRUTURA AUTOMATA
  SetAutomataFinalState(estrutura_automata, 6);
  AddAutomataTransition(estrutura_automata, 5, 6, delimiter_semicolon_check_automata);
  AddAutomataTransition(estrutura_automata, 4, 5, delimiter_close_braces_check_automata);
  AddAutomataTransition(estrutura_automata, 4, 4, declaracao_automata);
  AddAutomataTransition(estrutura_automata, 3, 4, declaracao_automata);
  AddAutomataTransition(estrutura_automata, 2, 3, delimiter_open_braces_check_automata);
  AddAutomataTransition(estrutura_automata, 1, 2, nome_automata);
  AddAutomataTransition(estrutura_automata, 0, 1, keyword_struct_check_automata);

  //FUNCOES AUTOMATA
  SetAutomataFinalState(funcoes_automata, 2);
  AddAutomataTransition(funcoes_automata, 1, 2, main_automata);
  AddAutomataTransition(funcoes_automata, 1, 1, implementacao_automata);
  AddAutomataTransition(funcoes_automata, 0, 1, implementacao_automata);

  //IMPLEMENTACAO AUTOMATA
  SetAutomataFinalState(implementacao_automata, 9);
  AddAutomataTransition(implementacao_automata, 8, 9, delimiter_close_braces_check_automata);
  AddAutomataTransition(implementacao_automata, 7, 8, comandos_funcao_automata);
  AddAutomataTransition(implementacao_automata, 6, 7, dados_automata);
  AddAutomataTransition(implementacao_automata, 5, 6, delimiter_open_braces_check_automata);
  AddAutomataTransition(implementacao_automata, 4, 5, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(implementacao_automata, 4, 3, delimiter_comma_check_automata);
  AddAutomataTransition(implementacao_automata, 3, 4, parametro_automata);
  AddAutomataTransition(implementacao_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(implementacao_automata, 1, 2, nome_automata);
  AddAutomataTransition(implementacao_automata, 0, 1, tipo_nome_automata);

  //TIPO_NOME AUTOMATA
  SetAutomataFinalState(tipo_nome_automata, 1);
  AddAutomataTransition(tipo_nome_automata, 0, 1, nome_automata);
  AddAutomataTransition(tipo_nome_automata, 0, 1, tipo_base_automata);

  //DADOS AUTOMATA
  SetAutomataFinalState(dados_automata, 4);
  AddAutomataTransition(dados_automata, 3, 4, delimiter_close_braces_check_automata);
  AddAutomataTransition(dados_automata, 3, 3, declaracao_automata);
  AddAutomataTransition(dados_automata, 2, 3, declaracao_automata);
  AddAutomataTransition(dados_automata, 1, 2, delimiter_open_braces_check_automata);
  AddAutomataTransition(dados_automata, 0, 1, keyword_data_check_automata);

  //ASSINATURAS AUTOMATA
  SetAutomataFinalState(assinaturas_automata, 4);
  AddAutomataTransition(assinaturas_automata, 3, 4, delimiter_close_braces_check_automata);
  AddAutomataTransition(assinaturas_automata, 3, 3, assinatura_automata);
  AddAutomataTransition(assinaturas_automata, 2, 3, assinatura_automata);
  AddAutomataTransition(assinaturas_automata, 1, 2, delimiter_open_braces_check_automata);
  AddAutomataTransition(assinaturas_automata, 0, 1, keyword_functions_check_automata);

  //ASSINATURAS AUTOMATA
  SetAutomataFinalState(assinatura_automata, 6);
  AddAutomataTransition(assinatura_automata, 5, 6, delimiter_semicolon_check_automata);
  AddAutomataTransition(assinatura_automata, 4, 5, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(assinatura_automata, 4, 3, delimiter_comma_check_automata);
  AddAutomataTransition(assinatura_automata, 3, 4, parametro_automata);
  AddAutomataTransition(assinatura_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(assinatura_automata, 1, 2, nome_automata);
  AddAutomataTransition(assinatura_automata, 0, 1, tipo_nome_automata);

  //PARAMETRO AUTOMATA
  SetAutomataFinalState(parametro_automata, 2);
  AddAutomataTransition(parametro_automata, 1, 2, nome_automata);
  AddAutomataTransition(parametro_automata, 0, 1, tipo_nome_automata);

  //DECLARACAO AUTOMATA
  SetAutomataFinalState(declaracao_automata, 4);
  AddAutomataTransition(declaracao_automata, 6, 4, delimiter_semicolon_check_automata);
  AddAutomataTransition(declaracao_automata, 5, 6, delimiter_close_brackets_check_automata);
  AddAutomataTransition(declaracao_automata, 3, 5, inteiro_automata);
  AddAutomataTransition(declaracao_automata, 2, 4, delimiter_semicolon_check_automata);
  AddAutomataTransition(declaracao_automata, 2, 3, delimiter_open_brackets_check_automata);
  AddAutomataTransition(declaracao_automata, 1, 2, nome_automata);
  AddAutomataTransition(declaracao_automata, 0, 1, tipo_nome_automata);

  //COMANDOS_FUNCAO AUTOMATA
  SetAutomataFinalState(comandos_funcao_automata, 2);
  AddAutomataTransition(comandos_funcao_automata, 1, 2, retorno_automata);
  AddAutomataTransition(comandos_funcao_automata, 0, 1, lista_comandos_automata);

  //LISTA_COMANDOS AUTOMATA
  SetAutomataFinalState(lista_comandos_automata, 1);
  AddAutomataTransition(lista_comandos_automata, 1, 1, comando_automata);
  AddAutomataTransition(lista_comandos_automata, 0, 1, comando_automata);

  //COMANDO AUTOMATA
  SetAutomataFinalState(comando_automata, 1);
  AddAutomataTransition(comando_automata, 0, 1, impressao_automata);
  AddAutomataTransition(comando_automata, 0, 1, leitura_automata);
  AddAutomataTransition(comando_automata, 0, 1, while_automata);
  AddAutomataTransition(comando_automata, 0, 1, ifelse_automata);
  AddAutomataTransition(comando_automata, 0, 1, if_automata);
  AddAutomataTransition(comando_automata, 0, 1, atribuicao_automata);

  //ATRIBUICAO AUTOMATA
  SetAutomataFinalState(atribuicao_automata, 4);
  AddAutomataTransition(atribuicao_automata, 3, 4, delimiter_semicolon_check_automata);
  AddAutomataTransition(atribuicao_automata, 2, 3, caractere_automata);
  AddAutomataTransition(atribuicao_automata, 2, 3, expressao_automata);
  AddAutomataTransition(atribuicao_automata, 1, 2, operator_equal_check_automata);
  AddAutomataTransition(atribuicao_automata, 0, 1, nome_automata);

  //EXPRESSAO AUTOMATA
  SetAutomataFinalState(expressao_automata, 1);
  AddAutomataTransition(expressao_automata, 0, 1, booleana_automata);
  AddAutomataTransition(expressao_automata, 0, 1, aritmetica_automata);

  //ARITIMETICA AUTOMATA
  SetAutomataFinalState(aritmetica_automata, 1);
  AddAutomataTransition(aritmetica_automata, 1, 0, operator_minus_check_automata);
  AddAutomataTransition(aritmetica_automata, 1, 0, operator_plus_check_automata);
  AddAutomataTransition(aritmetica_automata, 0, 1, termo_arita_automata);

  //TERMO_ARITA AUTOMATA
  SetAutomataFinalState(termo_arita_automata, 1);
  AddAutomataTransition(termo_arita_automata, 1, 0, operator_mod_check_automata);
  AddAutomataTransition(termo_arita_automata, 1, 0, operator_div_check_automata);
  AddAutomataTransition(termo_arita_automata, 1, 0, operator_mult_check_automata);
  AddAutomataTransition(termo_arita_automata, 0, 1, fator_arit_automata);

  //FATOR_ARIT AUTOMATA
  SetAutomataFinalState(fator_arit_automata, 1);
  AddAutomataTransition(fator_arit_automata, 4, 1, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(fator_arit_automata, 3, 4, aritmetica_automata);
  AddAutomataTransition(fator_arit_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(fator_arit_automata, 2, 1, numero_automata);
  AddAutomataTransition(fator_arit_automata, 0, 1, variavel_automata);
  AddAutomataTransition(fator_arit_automata, 0, 1, chamada_automata);
  AddAutomataTransition(fator_arit_automata, 0, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(fator_arit_automata, 0, 2, operator_minus_check_automata);
  AddAutomataTransition(fator_arit_automata, 0, 1, numero_automata);

  //VARIAVEL AUTOMATA
  SetAutomataFinalState(variavel_automata, 1);
  SetAutomataFinalState(variavel_automata, 5);
  AddAutomataTransition(variavel_automata, 4, 5, delimiter_close_brackets_check_automata);
  AddAutomataTransition(variavel_automata, 3, 5, nome_automata);
  AddAutomataTransition(variavel_automata, 2, 4, inteiro_automata);
  AddAutomataTransition(variavel_automata, 1, 3, operator_dot_check_automata);
  AddAutomataTransition(variavel_automata, 1, 2, delimiter_open_brackets_check_automata);
  AddAutomataTransition(variavel_automata, 0, 1, nome_automata);

  //RETORNO AUTOMATA
  SetAutomataFinalState(retorno_automata, 3);
  AddAutomataTransition(retorno_automata, 2, 3, delimiter_semicolon_check_automata);
  AddAutomataTransition(retorno_automata, 1, 2, expressao_automata);
  AddAutomataTransition(retorno_automata, 0, 1, keyword_return_check_automata);

  //MAIN AUTOMATA
  SetAutomataFinalState(main_automata, 8);
  AddAutomataTransition(main_automata, 7, 8, delimiter_close_braces_check_automata);
  AddAutomataTransition(main_automata, 6, 7, comandos_funcao_automata);
  AddAutomataTransition(main_automata, 5, 6, dados_automata);
  AddAutomataTransition(main_automata, 4, 5, delimiter_open_braces_check_automata);
  AddAutomataTransition(main_automata, 3, 4, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(main_automata, 2, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(main_automata, 1, 2, keyword_main_check_automata);
  AddAutomataTransition(main_automata, 0, 1, keyword_int_check_automata);

  //CHAMADA AUTOMATA
  SetAutomataFinalState(chamada_automata, 4);
  AddAutomataTransition(chamada_automata, 3, 4, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(chamada_automata, 2, 4, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(chamada_automata, 2, 3, lista_argumentos_automata);
  AddAutomataTransition(chamada_automata, 1, 2, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(chamada_automata, 0, 1, nome_automata);

  //LISTA_ARGUMENTOS AUTOMATA
  SetAutomataFinalState(lista_argumentos_automata, 1);
  AddAutomataTransition(lista_argumentos_automata, 1, 0, delimiter_comma_check_automata);
  AddAutomataTransition(lista_argumentos_automata, 0, 1, argumento_automata);

  //ARGUMENTO AUTOMATA
  SetAutomataFinalState(argumento_automata, 1);
  AddAutomataTransition(argumento_automata, 0, 1, caractere_automata);
  AddAutomataTransition(argumento_automata, 0, 1, expressao_automata);

  //IMPRESSAO AUTOMATA
  SetAutomataFinalState(impressao_automata, 6);
  AddAutomataTransition(impressao_automata, 5, 6, delimiter_close_parenthesis_check_automata);
  AddAutomataTransition(impressao_automata, 4, 5, expressao_automata);
  AddAutomataTransition(impressao_automata, 3, 5, string_automata);
  AddAutomataTransition(impressao_automata, 2, 4, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(impressao_automata, 1, 3, delimiter_open_parenthesis_check_automata);
  AddAutomataTransition(impressao_automata, 0, 2, keyword_println_check_automata);
  AddAutomataTransition(impressao_automata, 0, 2, keyword_print_check_automata);
  AddAutomataTransition(impressao_automata, 0, 1, keyword_printsln_check_automata);
  AddAutomataTransition(impressao_automata, 0, 1, keyword_prints_check_automata);

  return program_automata;
}

void eval(char* source_code) {
  Lexer lexer = InitLexer(source_code);
  Token *token;

  Automata *program = CreateProgramAutomata();
  token = GetAllTokens(&lexer);

  if(token == NULL) {
    printf("Error na posição %d do arquivo!\n", lexer.cursor);
    exit(-1);
  }

  token = ApplyAutomata(program, token, 0);
  PrintSeparator();
  if(token == NULL) {
    printf("Não foi possivel compilar o arquivo!\n");
    exit(-1);
  } else {
    printf("COMPILADO COM SUCESSO\n");
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
