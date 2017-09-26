#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include <string.h>
#include "token.h"

typedef struct _Automata {
  struct AutomataNode **transition_table;
  int states_length;
  int *final_states;
  int (*checker)(Token*);
  const char* name;
} Automata;

typedef struct _AutomataNode {
  struct AutomataNode *next;
  struct Automata *automata;
  int next_state;
} AutomataNode;

// Inicializa um novo Automata com states_length estados e com nome name
Automata *InitAutomata(int, const char*);

// Inicializa um novo Automata que serve apenas para checar se um token é aceito pela funcão checker
Automata *InitAutomataTransition(int (*checker)(Token *), const char*);

// Marca o estado state como um estado final do automato automata
void SetAutomataFinalState(Automata *, int);

// Adiciona uma nova transição na tabela de transições
void AddAutomataTransition(Automata *, int, int, Automata *);

// Checa se o automato é aceito a partir do token
Token *ApplyAutomata(Automata *, Token *, int);

#endif
