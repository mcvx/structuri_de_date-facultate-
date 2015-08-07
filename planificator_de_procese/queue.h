/* CRETU George Alexandru - 316CB */

#pragma once

#include <stdlib.h>
#include "list.h"

/* Semnatura functiei de comparare a informatiilor din coada */
typedef int (*TFComp)(void *a, void *b);

typedef struct
{
	TList l;
	size_t count;
	size_t infoSize;
	TFComp insertComp;
} TQueue;

/* Creeaza o coada noua
	<infoSize> = dimensiunea elementelor din coada
	<insertComp> = functia de compararea a elementelor in vederea introducerii ordonate
*/
TQueue* queue_new(size_t infoSize, TFComp insertComp);

/* Adauga un element in coada */
void queue_push(TQueue *q, void *info);

/* Extrage un element din coada si returneaza adresa informatiei */
void* queue_pop(TQueue *q);

/* Returneaza 1 daca este coada vida, 0 altfel */
int queue_isEmpty(TQueue *q);

/* Returneaza numarul de elemente din coada */
size_t queue_count(TQueue *q);

/* Curata coada
	<freeInfo> = functia de eliberare a informatiei din coada
*/
void queue_clear(TQueue *q, TFreeInfo freeInfo);

/* Distruge coada
	<freeInfo> = functia de eliberare a informatiei din coada
*/
void queue_destroy(TQueue **q, TFreeInfo freeInfo);

/* Afiseaza coada
	<freeInfo> = functia de afisare a informatiei din coada
*/
void queue_print(TQueue *q, TFPrintElem print_elem);