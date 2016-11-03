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

Automata* automata_init(int states_length, const char* name) {
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

Automata* automata_transition_init(int (*checker)(Token*), const char* name) {
  Automata* automata = automata_init(0, name);

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
  AutomataNode* first_automata_node = automata->transition_table[initial_state];
  AutomataNode* new_automata_node = automata_node_init(transition_automata, final_state, first_automata_node);

  automata->transition_table[initial_state] = new_automata_node;
}

char* string_spaces(int spaces) {
  char* string = malloc(sizeof(char) * (spaces + 1));

  for (size_t i = 0; i < spaces; i++) {
    string[i] = '-';
  }

  return string;
}

Token* automata_apply(Automata* automata, Token* token, int spaces) {
  int current_state = 0;
  Token* current_token = token;
  Token* next_token = NULL;
  printf("\n\n\n%sName: %s\n", string_spaces(spaces), automata->name);
  token_print(token);
  getchar();

  // while(next_token = automata_apply())
  if(automata->checker != NULL) {
    printf("%sTem checher!\n", string_spaces(spaces));
    int accepted = (*automata->checker)(current_token);
    if(accepted) {
      printf("%sFoi aceito!!\n", string_spaces(spaces));
      return current_token->next;
    }
    else {
      printf("%sNão foi aceito!!\n", string_spaces(spaces));
      return NULL;
    }
  }
  else {
    printf("%sNão tem checher!\n", string_spaces(spaces));
    while(!automata->final_states[current_state]) {
      AutomataNode *automata_transition = automata->transition_table[current_state];

      if(automata_transition == NULL) {
        printf("%sEsse cara não tem nenhum automata!!!\n", string_spaces(spaces));
      }

      while(automata_transition != NULL) {
        next_token = automata_apply(automata_transition->automata, current_token, spaces + 1);
        if(next_token != NULL) {
          current_token = next_token;
          current_state = automata_transition->next_state;
          break;
        }
      }
      if(next_token == NULL) {
        return NULL;
      }
    }
  }

  return NULL;
}
