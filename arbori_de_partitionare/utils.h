/* CRETU George Alexandru - 316CB */

#pragma once

typedef struct point
{
	int x;
	int y;
	int index;
} TPoint;

typedef struct line
{
	int a;
	int b;
	int c;
} TLine;

/* Returneaza 1 daca dreptele date ca parametru sunt paralele - 0 in caz contrar */
int is_parallel(TLine *d, TLine *e);

/* Evalueaza ecuatia unei drepte <d> in punctul <p> si returneaza rezultatul */
double evaluate(TLine *d, TPoint *p);

/* Aloca o dreapta */
TLine* allocLine(int a, int b, int c);

/* Aloca un punct */
TPoint* allocPoint(int x, int y, int index);