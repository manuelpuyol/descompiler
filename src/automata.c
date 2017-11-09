#include "automata.h"

AutomataList *InitAutomataList() {
  AutomataList *list = (AutomataList *)malloc(sizeof(AutomataList));

  list->head = NULL;
  list->end = NULL;

  return list;
}

void AddAutomataToList(AutomataList *list, Automata *automata) {
  if(list->head == NULL) {
    list->head = automata;
    list->end = automata;
  } else {
    Automata *tmp = list->end;
    tmp->next = automata;
    automata->prev = tmp;
    list->end = automata;
  }
}

Automata *InitAutomata(AutomataList *list, int states_length, const char* name) {
  Automata *automata = malloc(sizeof (Automata));

  automata->name = name;
  automata->states_length = states_length;
  automata->final_states = (int*) malloc(sizeof(int) * states_length);
  automata->transition_table = (AutomataNode**) malloc(sizeof(AutomataNode*) * states_length);
  automata->checker = NULL;
  automata->next = NULL;
  automata->prev = NULL;

  for (size_t i = 0; i < states_length; i++) {
    automata->final_states[i] = 0;
    automata->transition_table[i] = NULL;
  }

  AddAutomataToList(list, automata);

  return automata;
}

Automata *InitAutomataTransition(AutomataList *list, int (*checker)(Token*, int), const char* name) {
  Automata *automata = InitAutomata(list, 0, name);

  automata->checker = checker;

  return automata;
}

AutomataNode *InitAutomataNode(Automata *automata, int next_state, AutomataNode *next) {
  AutomataNode *node = (AutomataNode *)malloc(sizeof(AutomataNode));

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
  AutomataNode *new_automata_node = InitAutomataNode(transition_automata, final_state, first_automata_node);

  automata->transition_table[initial_state] = new_automata_node;
}

Token *ApplyAutomata(Automata *automata, Token *token, int spaces) {
  int current_state = 0;
  Token *current_token = token;
  Token *next_token = NULL;

  PrintSeparator();
  PrintAux(spaces);
  printf("NOME: %s\n", automata->name);

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
    PrintAux(spaces);
    printf("ESTADO = %d\n", current_state);
    while(1) {
      AutomataNode *automata_transition = automata->transition_table[current_state];
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
        PrintAux(spaces);
        printf("%s SEM TOKEN\n", automata->name);
        break;
      } else {
        PrintAux(spaces);
        printf("NEXT TOKEN STATE = %d %d\n", current_state, automata->final_states[current_state]);
      }
    }
    PrintAux(spaces);
    printf("FIM DO LOOP -- %s %d\n", GetTokenValue(current_token), automata->final_states[current_state]);
    if(automata->final_states[current_state]) {
      return current_token;
    }
    return NULL;
  }
  return NULL;
}

void FreeAutomatas(AutomataList *list) {
  Automata *tmp;
  Automata *automata = list->head;

  while(automata != NULL) {
    tmp = automata->next;
    FreeAutomata(automata);
    automata = tmp;
  }

  free(list);
}

void FreeAutomata(Automata *automata) {
  for (size_t i = 0; i < automata->states_length; i++) {
    free(automata->transition_table[i]);
  }

  free(automata->final_states);
  free(automata->transition_table);
  free(automata);
}