/* CRETU George Alexandru - 316CB */

#include "stack.h"

#include <string.h>
#include <stdio.h>

TStack* stack_new(size_t infoSize)
{
	TStack *s = calloc(1, sizeof(TStack));
	s->count = 0;
	s->infoSize = infoSize;
	s->l = NULL;

	return s;
}

void stack_push(TStack *s, void *info)
{
	list_insert(&(s->l), info, s->infoSize);
	s->count++;
}

void* stack_pop(TStack *s)
{
	if (s->l == NULL)
	{
		return NULL;
	}

	void *info = s->l->info;

	TList aux = s->l;
	s->l = aux->next;
	free(aux);

	s->count--;

	return info;
}

int stack_isEmpty(TStack *s)
{
	return s->l == NULL;
}

size_t stack_count(TStack *s)
{
	return s->count;
}

void stack_clear(TStack *s, TFreeInfo freeInfo)
{
	list_destroy(&(s->l), freeInfo);
	s->count = 0;
}

void stack_destroy(TStack **s, TFreeInfo freeInfo)
{
	list_destroy(&((*s)->l), freeInfo);
	free(*s);
	*s = NULL;
}

void stack_print(TStack *s, TFPrintElem print_elem)
{
	list_print(&(s->l), print_elem);
}