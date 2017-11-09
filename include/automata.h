#ifndef _AUTOMATA_H_
#define _AUTOMATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

typedef struct _AutomataNode {
  struct AutomataNode *next;
  struct Automata *automata;
  int next_state;
} AutomataNode;

typedef struct _Automata {
  AutomataNode **transition_table;
  int states_length;
  int *final_states;
  int (*checker)(Token *, int);
  const char *name;
  struct Automata *next, *prev;
} Automata;

typedef struct _AutomataList {
  Automata *head, *end;
} AutomataList;

AutomataList *InitAutomataList();
Automata *InitAutomata(AutomataList *, int, const char *);
Automata *InitAutomataTransition(AutomataList *,int (*checker)(Token *, int), const char *);
void SetAutomataFinalState(Automata *, int );
void AddAutomataTransition(Automata *, int, int, Automata *);
Token *ApplyAutomata(Automata *, Token *, int);
void FreeAutomatas(AutomataList *);

#endif
