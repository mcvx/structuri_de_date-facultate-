/* CRETU George Alexandru - 316CB */

#include "queue.h"

#include <string.h>

TQueue* queue_new(size_t infoSize, TFComp insertComp)
{
	TQueue *q = calloc(1, sizeof(TQueue));
	q->count = 0;
	q->infoSize = infoSize;
	q->l = NULL;
	q->insertComp = insertComp;

	return q;
}

void queue_push(TQueue *q, void *info)
{
	TList *l = &(q->l);

	while (*l && q->insertComp((*l)->info, info) > 0)
	{
		l = &(*l)->next;
	}

	TList aux = calloc(1, sizeof(TCell));
	aux->info = calloc(1, q->infoSize);
	memcpy(aux->info, info, q->infoSize);

	aux->next = *l;
	*l = aux;

	q->count++;
}

void* queue_pop(TQueue *q)
{
	if (q->l == NULL)
	{
		return NULL;
	}

	void *info = q->l->info;

	TList aux = q->l;
	q->l = aux->next;
	free(aux);

	q->count--;

	return info;
}

int queue_isEmpty(TQueue *q)
{
	return q->l == NULL;
}

size_t queue_count(TQueue *q)
{
	return q->count;
}

void queue_clear(TQueue *q, TFreeInfo freeInfo)
{
	list_destroy(&(q->l), freeInfo);
	q->count = 0;
}

void queue_destroy(TQueue **q, TFreeInfo freeInfo)
{
	list_destroy(&((*q)->l), freeInfo);
	free(*q);
	*q = NULL;
}

void queue_print(TQueue *q, TFPrintElem print_elem)
{
	list_print(&(q->l), print_elem);
}