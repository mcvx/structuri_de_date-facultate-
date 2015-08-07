/* CRETU George Alexandru - 316CB */

#pragma once

#include <stdlib.h>
#include "list.h"

typedef struct
{
	TList l;
	size_t count;
	size_t infoSize;
} TStack;

/* Creeaza o stiva noua
	<infoSize> = dimensiunea elementelor din stiva
*/
TStack* stack_new(size_t infoSize);

/* Adauga un element in stiva */
void stack_push(TStack *s, void *info);

/* Extrage un element din stiva si returneaza adresa informatiei */
void* stack_pop(TStack *s);

/* Returneaza 1 daca este stiva vida, 0 altfel */
int stack_isEmpty(TStack *s);

/* Returneaza numarul de elemente din stiva */
size_t stack_count(TStack *s);

/* Curata stiva
	<freeInfo> = functia de eliberare a informatiei din stiva
*/
void stack_clear(TStack *s, TFreeInfo freeInfo);

/* Distruge stiva
	<freeInfo> = functia de eliberare a informatiei din stiva
*/
void stack_destroy(TStack **s, TFreeInfo freeInfo);

/* Afiseaza stiva
	<freeInfo> = functia de afisare a informatiei din stiva
*/
void stack_print(TStack *s, TFPrintElem print_elem);