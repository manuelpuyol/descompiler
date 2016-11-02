#include <stdio.h>
#include <stdlib.h>
#include "automata.h"
#include "token.h"

// typedef struct Automata {
//   struct AutomataNode **transition_table;
//   int states_length;
//   int* final_states;
//   int (*checker)(Token*);
// } Automata;
//
// typedef struct AutomataNode {
//   struct AutomataNode *next;
//   struct Automata *automata;
//   int next_state;
// } AutomataNode;

Automata* automata_init(int states_length) {
  Automata* automata = malloc(sizeof (Automata));

  automata->states_length = states_length;
  automata->final_states = (int*) malloc(sizeof(int) * states_length);
  automata->transition_table = (AutomataNode**) malloc(sizeof(AutomataNode*) * states_length);


  for (size_t i = 0; i < states_length; i++) {
    automata->final_states[i] = 0;
  }

  return automata;
}

Automata* automata_transition_init(int (*checker)(Token*)) {
  Automata* automata = automata_init(0);

  automata->checker = checker;

  return automata;
}

AutomataNode* automata_node_init(Automata* automata, int next_state, AutomataNode* next) {
  AutomataNode* node = malloc(sizeof (AutomataNode));

  node->next = next;
  node->automata = automata;
  node->next_state = next_state;

  return node;
}

void automata_set_final_state(Automata* automata, int state) {
  automata->final_states[state] = 1;
}

void automata_add_transition(Automata* automata, int initial_state, int final_state, Automata* transition_automata) {
  return;
  AutomataNode* first_automata_node = automata->transition_table[initial_state];
  AutomataNode* new_automata_node = automata_node_init(transition_automata, final_state, first_automata_node);

  automata->transition_table[initial_state] = new_automata_node;
}
