#include <stdio.h>
#include <stdlib.h>
#include "automata.h"
#include "token.h"

Automata* InitAutomata(int states_length, const char* name) {
  Automata* automata = malloc(sizeof (Automata));

  automata->name = name;
  automata->states_length = states_length;
  automata->final_states = (int*) malloc(sizeof(int) * states_length);
  automata->transition_table = (AutomataNode**) malloc(sizeof(AutomataNode*) * states_length);
  automata->checker = NULL;

  for (size_t i = 0; i < states_length; i++) {
    automata->final_states[i] = 0;
    automata->transition_table[i] = NULL;
  }

  return automata;
}

Automata* InitAutomataTransition(int (*checker)(Token*), const char* name) {
  Automata* automata = InitAutomata(0, name);

  automata->checker = checker;

  return automata;
}

AutomataNode* InitAutomataNode(Automata* automata, int next_state, AutomataNode* next) {
  AutomataNode* node = malloc(sizeof (AutomataNode));

  node->next = next;
  node->automata = automata;
  node->next_state = next_state;

  return node;
}

void SetAutomataFinalState(Automata* automata, int state) {
  automata->final_states[state] = 1;
}

void AddAutomataTransition(Automata* automata, int initial_state, int final_state, Automata* transition_automata) {
  AutomataNode* first_automata_node = automata->transition_table[initial_state];
  AutomataNode* new_automata_node = InitAutomataNode(transition_automata, final_state, first_automata_node);

  automata->transition_table[initial_state] = new_automata_node;
}

Token* AppyAutomata(Automata* automata, Token* token) {
  int current_state = 0;
  Token* current_token = token;
  printf("Name: %s\n", automata->name);

  if(automata->checker != NULL) {
    int accepted = (*automata->checker)(current_token);
    if(accepted) {
      return current_token->next;
    }
    else {
      return NULL;
    }
  }
  else {
    printf("current_state %d\n", current_state);
    AutomataNode* automata_node = automata->transition_table[current_state];

    if(automata_node != NULL) {
      Token* token_result = AppyAutomata(automata_node->automata, current_token);

      if(token_result != NULL) {
        current_token = token_result;
        current_state = automata_node->next_state;
      }
    }
  }

  return NULL;
}
