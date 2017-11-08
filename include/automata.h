#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include <string.h>
#include "token.h"

typedef struct _Automata {
  struct AutomataNode **transition_table;
  int states_length;
  int *final_states;
  int (*checker)(Token *);
  const char *name;
} Automata;

typedef struct _AutomataNode {
  struct AutomataNode *next;
  struct Automata *automata;
  int next_state;
} AutomataNode;

Automata *InitAutomata(int, const char *);
Automata *InitAutomataTransition(int (*checker)(Token *), const char *);
void SetAutomataFinalState(Automata *, int );
void AddAutomataTransition(Automata *, int, int, Automata *);
Token *AppyAutomata(Automata *, Token *);

#endif
