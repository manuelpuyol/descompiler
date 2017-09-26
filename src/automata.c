#include <stdio.h>
#include <stdlib.h>
#include "automata.h"
#include "token.h"

Automata *InitAutomata(int states_length, const char *name) {
  Automata *automata = malloc(sizeof (Automata));

  automata->name = name;
  automata->states_length = states_length;
  automata->final_states = (int *) malloc(sizeof(int) * states_length);
  automata->transition_table = (AutomataNode**) malloc(sizeof(AutomataNode*) * states_length);
  automata->checker = NULL;

  for (size_t i = 0; i < states_length; i++) {
    automata->final_states[i] = 0;
    automata->transition_table[i] = NULL;
  }

  return automata;
}

Automata *InitAutomataTransition(int (*checker)(Token*), const char *name) {
  Automata *automata = InitAutomata(0, name);

  automata->checker = checker;

  return automata;
}

AutomataNode *automata_node_init(Automata *automata, int next_state, AutomataNode* next) {
  AutomataNode* node = malloc(sizeof (AutomataNode));

  node->next = next;
  node->automata = automata;
  node->next_state = next_state;

  return node;
}

void SetAutomataFinalState(Automata *automata, int state) {
  automata->final_states[state] = 1;
}

void AddAutomataTransition(Automata *automata, int initial_state, int final_state, Automata *transition_automata) {
  AutomataNode *first_automata_node = automata->transition_table[initial_state];
  AutomataNode *new_automata_node = automata_node_init(transition_automata, final_state, first_automata_node);

  automata->transition_table[initial_state] = new_automata_node;
}

char *StringSpaces(int spaces) {
  char *string = malloc(sizeof(char) * (spaces + 1));

  for (size_t i = 0; i < spaces; i++) {
    string[i] = '-';
  }

  return string;
}

Token* ApplyAutomata(Automata *automata, Token *token, int spaces) {
  int current_state = 0;
  Token *current_token = token;
  Token *next_token = NULL;
  // getchar();
  printf("\n\n\n%sName: %s\n", StringSpaces(spaces), automata->name);
  PrintToken(token);

  // while(next_token = ApplyAutomata())
  if(automata->checker != NULL) {
    printf("%sTem checher!\n", StringSpaces(spaces));
    int accepted = (*automata->checker)(current_token);
    if(accepted) {
      printf("%sFoi aceito!!\n", StringSpaces(spaces));
      return current_token->next;
    }
    else {
      printf("%sNão foi aceito!!\n", StringSpaces(spaces));
      return NULL;
    }
  }
  else {
    printf("%sNão tem checher!\n", StringSpaces(spaces));
    while(1) {
      AutomataNode *automata_transition = automata->transition_table[current_state];

      if(automata_transition == NULL) {
        printf("%sEsse cara não tem nenhum automata!!!\n", StringSpaces(spaces));
        break;
      }

      while(automata_transition != NULL) {
        next_token = ApplyAutomata(automata_transition->automata, current_token, spaces + 1);
        if(next_token != NULL) {
          printf("%s %s %d Voltou com um next_token: %s!!!\n", StringSpaces(spaces), automata->name, current_state, GetTokenValue(next_token));
          current_token = next_token;
          current_state = automata_transition->next_state;
          break;
        }
        automata_transition = automata_transition->next;
      }
      if(next_token == NULL) {
        printf("%s %s Saiu do loop sem next_token!!!\n", StringSpaces(spaces), automata->name);
        break;
      }
      else {
        printf("%sSaiu do loop com next_token State: %d %d!!!\n", StringSpaces(spaces), current_state, automata->final_states[current_state]);
      }
    }
    printf("%sSaiu do loop principal!!! %s %d\n", StringSpaces(spaces), GetTokenValue(current_token), automata->final_states[current_state]);
    if(automata->final_states[current_state]) {
      return current_token;
    }
    return NULL;
  }

  return NULL;
}
