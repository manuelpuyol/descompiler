#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include <string.h>
#include "token.h"

typedef struct Automata {
  struct AutomataNode **transition_table;
  int states_length;
  int* final_states;
  int (*checker)(Token*);
  const char* name;
} Automata;

typedef struct AutomataNode {
  struct AutomataNode *next;
  struct Automata *automata;
  int next_state;
} AutomataNode;

// Inicializa um novo Automata com states_length estados e com nome name
Automata* automata_init(int states_length, const char* name);

// Inicializa um novo Automata que serve apenas para checar se um token é aceito pela funcão checker
Automata* automata_transition_init(int (*checker)(Token*), const char* name);

// Marca o estado state como um estado final do automato automata
void automata_set_final_state(Automata* automata, int state);

// Adiciona uma nova transição na tabela de transições
void automata_add_transition(Automata* automata, int initial_state, int final_state, Automata* transition_function);

// Checa se o automato é aceito a partir do token
Token* automata_apply(Automata* automata, Token* token, int spaces);

#endif
