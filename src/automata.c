#include "automata.h"

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

Automata* InitAutomataTransition(int (*checker)(Token*, int), const char* name) {
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

Token *ApplyAutomata(Automata* automata, Token* token, int spaces) {
  int current_state = 0;
  Token* current_token = token;
  Token* next_token = NULL;

  PrintSeparator();
  printf("%s NOME: %s\n", PrintAux(spaces), automata->name);

  if(automata->checker != NULL) {
    // printf("TEM CHECKER\n");
    int accepted = (*automata->checker)(current_token, spaces);
    if(accepted) {
      // printf("ACEITO\n");
      return current_token->next;
    }
    else {
      // printf("NAO ACEITO\n");
      return NULL;
    }
  }
  else {
    // printf("NAO TEM CHECKER\n");
    printf("%s ESTADO = %d\n", PrintAux(spaces), current_state);
    while(1) {
      AutomataNode* automata_transition = automata->transition_table[current_state];
      if(automata_transition == NULL) {
        // printf("SEM AUTOMATO\n");
        break;
      }

      while(automata_transition != NULL) {
        next_token = ApplyAutomata(automata_transition->automata, current_token, spaces + 1);
        if(next_token != NULL) {
          // printf("COM NEXT TOKEN\n");
          current_token = next_token;
          current_state = automata_transition->next_state;
          break;
        }
        automata_transition = automata_transition->next;
      }
      if(next_token == NULL) {
        printf("%s %s SEM TOKEN\n", PrintAux(spaces), automata->name);
        break;
      } else {
        printf("%s NEXT TOKEN STATE = %d %d\n", PrintAux(spaces), current_state, automata->final_states[current_state]);
      }
    }
    printf("%s FIM DO LOOP -- %s %d\n", PrintAux(spaces), GetTokenValue(current_token), automata->final_states[current_state]);
    if(automata->final_states[current_state]) {
      return current_token;
    }
    return NULL;
  }
  return NULL;
}
