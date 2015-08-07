/* CRETU George Alexandru - 316CB */

#include "bsp_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __bspTree_destroyAux(TBspTree t)
{
	if (t)
	{
		__bspTree_destroyAux(t->left);
		__bspTree_destroyAux(t->right);

		if (t->d)
		{
			free(t->d);
		}

		if (t->p)
		{
			free(t->p);
		}

		free(t);
	}
}

void __bspTree_printAux(TBspTree t)
{
	if (!t)
	{
		printf("null");
	}
	else if (t->d)
	{
		__bspTree_printAux(t->left);
		__bspTree_printAux(t->right);

		printf("(%d,%d,%d)", t->d->a, t->d->b, t->d->c);
	}
	else
	{
		printf("((%d,%d)-%d)", t->p->x, t->p->y, t->p->index);
	}
}

TNode* bspTree_allocNode()
{
	TBspTree t = calloc(1, sizeof(TNode));

	if (!t)
	{
		return NULL;
	}

	t->left = t->right = NULL;
	t->p = NULL;
	t->d = NULL;

	return t;
}

void bspTree_insertLine(TBspTree *t, TLine *d)
{
	if (!*t)
	{
		*t = bspTree_allocNode();

		if (!*t)
		{
			printf("Nu s-a putut aloca un nod nou!\n");
			return;
		}

		(*t)->d = allocLine(d->a, d->b, d->c);
		if (!(*t)->d)
		{
			printf("Nu s-a putut aloca dreapta!\n");
			return;
		}

		return;
	}

	if (is_parallel((*t)->d, d))
	{
		if ((*t)->d->c < d->c)
		{
			bspTree_insertLine(&(*t)->left, d);
		}
		else
		{
			bspTree_insertLine(&(*t)->right, d);
		}
	}
	else
	{
		bspTree_insertLine(&(*t)->left, d);
		bspTree_insertLine(&(*t)->right, d);
	}
}

void bspTree_insertPoint(TBspTree *t, TPoint *p)
{
	if (!*t)
	{
		*t = bspTree_allocNode();

		if (!*t)
		{
			printf("Nu s-a putut aloca un nod nou!\n");
			return;
		}

		(*t)->p = allocPoint(p->x, p->y, p->index);
		if (!(*t)->p)
		{
			printf("Nu s-a putut aloca punctul!\n");
			return;
		}

		return;
	}

	if (!(*t)->d)
	{
		return;
	}

	if (evaluate((*t)->d, p) <= 0)
	{
		bspTree_insertPoint(&(*t)->left, p);
	}
	else
	{
		bspTree_insertPoint(&(*t)->right, p);
	}
}

void bspTree_destroy(TBspTree *t)
{
	__bspTree_destroyAux(*t);
	*t = NULL;
}

void bspTree_print(TBspTree t)
{
	__bspTree_printAux(t);
	printf("\n");
}