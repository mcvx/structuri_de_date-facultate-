/* CRETU George Alexandru - 316CB */

#pragma once

#include <stdlib.h>

typedef struct cell
{
	struct cell *next;
	void *info;
} TCell, *TList;

// Semnatura functiei de printare a informatiei unui element din lista
typedef void (*TFPrintElem)(void*);

// Semnatura functiei de eliberare a memoriei folosita de informatia unui element din lista
typedef void (*TFreeInfo)(void*);


// Insereaza un element la inceputul listei
int list_insert(TList *list, void *info, size_t infoSize);

// Sterge un element din lista       
void list_remove(TList *elem, TFreeInfo freeInfo);

// Distruge lista
void list_destroy(TList *list, TFreeInfo freeInfo);

// Returneaza numarul de elemente ale listei
size_t list_length(TList *list);

// Afiseaza lista
void list_print(TList *list, TFPrintElem print_elem);