/* CRETU George Alexandru - 316CB */

#pragma once

#include "utils.h"

typedef struct node
{
	TLine *d;
	TPoint *p;
	struct node *left, *right;
} TNode, *TBspTree;

/* Functie auxiliara pentru distrugerea arborelui */
void __bspTree_destroyAux(TBspTree t);

/* Functie auxiliara pentru afisarea arborelui */
void __bspTree_printAux(TBspTree t);


/* Aloca un nod nou */
TNode* bspTree_allocNode();

/* Insereaza o dreapta in arbore */
void bspTree_insertLine(TBspTree *t, TLine *d);

/* Insereaza un punct de identificare in arbore */
void bspTree_insertPoint(TBspTree *t, TPoint *p);

/* Distruge arborele */
void bspTree_destroy(TBspTree *t);

/* Afiseaza arborele in postordine */
void bspTree_print(TBspTree t);