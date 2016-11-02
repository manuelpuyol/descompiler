#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include <string.h>
#include "token.h"

typedef struct Automata {
  struct AutomataNode **transition_table;
  int states_length;
  int* final_states;
  int (*checker)(Token*);
} Automata;

typedef struct AutomataNode {
  struct AutomataNode *next;
  struct Automata *automata;
  int next_state;
} AutomataNode;

Automata* automata_init(int states_length);
Automata* automata_transition_init(int (*checker)(Token*));
void automata_set_final_state(Automata* automata, int state);
void automata_add_transition(Automata* automata, int initial_state, int final_state, Automata* transition_function);
Token* automata_apply(Automata* automata, Token* token);

#endif
