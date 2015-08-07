/* CRETU George Alexandru - 316CB */

#include "utils.h"

#include <stdlib.h>

int is_parallel(TLine *d, TLine *e)
{
	return d->a * e->b == d->b * e->a;
}

double evaluate(TLine *d, TPoint *p)
{
	return d->a * p->x + d->b * p->y + d->c;
}

TLine* allocLine(int a, int b, int c)
{
	TLine *l = calloc(1, sizeof(TLine));

	if (!l)
	{
		return NULL;
	}

	l->a = a;
	l->b = b;
	l->c = c;

	return l;
}

TPoint* allocPoint(int x, int y, int index)
{
	TPoint *p = calloc(1, sizeof(TPoint));

	if (!p)
	{
		return NULL;
	}

	p->x = x;
	p->y = y;
	p->index = index;

	return p;
}