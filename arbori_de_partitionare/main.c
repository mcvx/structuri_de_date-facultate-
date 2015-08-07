/* CRETU George Alexandru - 316CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "bsp_tree.h"

/* Returneaza regiunea in care se afla punctul <p> */
int get_plane(TBspTree t, TPoint *p);

/* Reconstruieste arborele pe baza organizarii nodurilor utile */
void reconstruct(TBspTree *t, TLine *v);

int main(int argc, char *argv[])
{	
	int i, n, mod;
	TPoint p;
	TLine l;
	TBspTree t = NULL;
	FILE *inFile, *outFile;

	// Daca nu exista destule argumente la rularea programului, atunci opreste executia
	if (argc < 4)
	{
		printf("Argumente insuficiente!\n");
		return -1;
	}

	// Seteaza modul si fisierele de intrare si de iesire
 	mod = strtol(argv[1], NULL, 10);
	inFile = freopen(argv[2], "r", stdin);
	outFile = freopen(argv[3], "w", stdout);

	// Verifica daca s-au deschis fisierele
	if (!inFile)
	{
		printf("Nu s-a putut deschide fisierul de intrare!\n");
		return -1;
	}

	if (!outFile)
	{
		printf("Nu s-a putut deschide fisierul de iesire!\n");
		return -1;
	}

	// Selecteaza modul
	if (mod == 1) /* Modul 1 */
	{
		// Citeste dreptele si le salveaza intr-un vector
		scanf("%d", &n);
		TLine *lines = calloc(n, sizeof(TLine));

		for (i = 0; i < n; i++)
		{
			scanf("%d %d %d", &(lines[i].a), &(lines[i].b), &(lines[i].c));
		}

		// Citeste punctele de identificare si le salveaza intr-un vector
		scanf("%d", &n);
		TPoint *points = calloc(n, sizeof(TPoint));

		for (i = 0; i < n; i++)
		{
			scanf("%d %d", &(points[i].x), &(points[i].y));
			points[i].index = i;
		}

		// Construieste arborele
		reconstruct(&t, lines);

		// Insereaza punctele de identificare in arbore
		for (i = 0; i < n; i++)
		{
			bspTree_insertPoint(&t, &points[i]);
		}

		// Curata memoria
		free(lines);
		free(points);
	}
	else /* Modul 2 */
	{
		// Citeste dreptele si le insereaza in arbore
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			scanf("%d %d %d", &(l.a), &(l.b), &(l.c));

			bspTree_insertLine(&t, &l);
		}

		// Citeste punctele de identificare si le insereaza in arbore
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			scanf("%d %d", &(p.x), &(p.y));
			p.index = i;

			bspTree_insertPoint(&t, &p);
		}
	}

	// Afiseaza arborele
	bspTree_print(t);

	// Gaseste regiunea punctelor de interogare
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d %d", &(p.x), &(p.y));
		printf("%d\n", get_plane(t, &p));
	}

	// Curata memoria
	bspTree_destroy(&t);

	return 0;
}

int get_plane(TBspTree t, TPoint *p)
{
	while (t && t->d)
	{
		if (evaluate(t->d, p) <= 0)
		{
			t = t->left;
		}
		else
		{
			t = t->right;
		}
	}

	return t->p->index;
}

void reconstruct(TBspTree *t, TLine *v)
{
	int nod, efs, efd;
	scanf("%d %d %d", &nod, &efs, &efd);

	*t = bspTree_allocNode();
	if (!*t)
	{
		printf("Nu s-a putut aloca un nod nou!\n");
		return;
	}

	(*t)->d = allocLine(v[nod].a, v[nod].b, v[nod].c);
	if (!(*t)->d)
	{
		printf("Nu s-a putut aloca dreapta!\n");
		return;
	}

	if (efs)
	{
		reconstruct(&((*t)->left), v);
	}

	if (efd)
	{
		reconstruct(&((*t)->right), v);
	}
}