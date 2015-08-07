/* CRETU George Alexandru - 316CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "queue.h"

typedef struct 
{
	int id;
	int priority;
	int iteration;
} TProcess;

// Functie auxiliara pentru afisarea unei structuri de tip TProcess
void print_process(void *a);

// Functie auxiliara pentru distrugerea unei structuri de tip TProcess
void free_process(void *p);

// Functie auxiliara pentru compararea unei structuri de tip TProcess
int compare_process(void *a, void *b);

int main(int argc, char *argv[])
{
	char command[32];
	int eventsNr, eventId, procId, priority;
	int i, iteration;
	TStack **eventsStacks;
	TQueue *procQ;

	// Daca nu exista destule argumente la rularea programului, atunci opreste executia
	if (argc < 3)
	{
		printf("Argumente insuficiente!\n");
		return -1;
	}

	// Seteaza fisierele de intrare si de iesire
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);

	// Citeste numarul de event-uri si creeaza stivele lor
	fscanf(stdin, "%d", &eventsNr);

	eventsStacks = calloc(eventsNr,  sizeof(TStack*));
	for (i = 0; i < eventsNr; i++)
	{
		eventsStacks[i] = stack_new(sizeof(TProcess));
	}

	// Creeaza coada de prioritati
	procQ = queue_new(sizeof(TProcess), compare_process);

	// Citeste si executa comenzile din fisierul de intrare
	iteration = 0;

	while (fscanf(stdin, "%s", command) != EOF)
	{
		iteration++;

		if (strcmp(command, "start") == 0)
		{
			fscanf(stdin, "%d", &procId);
			fscanf(stdin, "%d", &priority);

			// Creeaza un proces
			TProcess p;
			p.id = procId;
			p.priority = priority;
			p.iteration = iteration;

			// Introduce procesul creat in coada de prioritati
			queue_push(procQ, &p);
		}
		else if (strcmp(command, "wait") == 0)
		{
			fscanf(stdin, "%d", &eventId);
			fscanf(stdin, "%d", &procId);

			// Creaza o stiva auxiliara
			TStack *aux = stack_new(sizeof(TProcess));

			// Muta procesele in stiva auxiliara pana cand procesul
			// cautat este gasit si mutat in stiva evenimentului
			TProcess *p;
			while (!queue_isEmpty(procQ))
			{
				p = queue_pop(procQ);

				if (p->id == procId)
				{
					stack_push(eventsStacks[eventId], p);
					free_process(p);
					break;
				}
				
				stack_push(aux, p);
				free_process(p);
			}

			// Muta procesele din stiva auxiliara inapoi in coada
			// de prioritati
			while (!stack_isEmpty(aux))
			{
				p = stack_pop(aux);
				queue_push(procQ, p);
				free_process(p);
			}

			// Distruge stiva auxiliara
			stack_destroy(&aux, free_process);
		}
		else if (strcmp(command, "event") == 0)
		{
			fscanf(stdin, "%d", &eventId);

			// Muta procesele din stiva evenimentului in coada
			// de prioritati
			TProcess *p;
			while (!stack_isEmpty(eventsStacks[eventId]))
			{
				p = stack_pop(eventsStacks[eventId]);
				queue_push(procQ, p);
				free_process(p);
			}
		}
		else if (strcmp(command, "end") == 0)
		{
			fscanf(stdin, "%d", &procId);

			// Creaza o stiva auxiliara
			TStack *aux = stack_new(sizeof(TProcess));

			// Muta procesele in stiva auxiliara pana cand procesul
			// cautat este gasit si sters
			TProcess *p;
			while (!queue_isEmpty(procQ))
			{
				p = queue_pop(procQ);

				if (p->id == procId)
				{
					free_process(p);
					break;
				}
				
				stack_push(aux, p);
				free_process(p);
			}

			// Muta procesele din stiva auxiliara inapoi in coada
			// de prioritati
			while (!stack_isEmpty(aux))
			{
				p = stack_pop(aux);
				queue_push(procQ, p);
				free_process(p);
			}

			// Distruge stiva auxiliara
			stack_destroy(&aux, free_process);
		}

		// Afiseaza iteratia
		printf("%d\n", iteration);

		// Afiseaza coada de prioritati
		if (!queue_isEmpty(procQ))
		{
			queue_print(procQ, print_process);
		}
		else
		{
			printf("\n");
		}

		// Afiseaza stivele
		for (i = 0; i < eventsNr; i++)
		{
			if (!stack_isEmpty(eventsStacks[i]))
			{
				printf("%d: ", i);
				stack_print(eventsStacks[i], print_process);
			}
		}

		printf("\n");
	}

	// Elibereaza memoria
	queue_destroy(&procQ, free_process);

	for (i = 0; i < eventsNr; i++)
	{
		stack_destroy(&eventsStacks[i], free_process);
	}
	free(eventsStacks);

	return 0;
}

void print_process(void *a)
{
	TProcess *p = a;
	printf("%d ", p->id);
}

void free_process(void *p)
{
	free(p);
}

int compare_process(void *a, void *b)
{
	TProcess *pa, *pb;
	pa = a;
	pb = b;

	if (pa->priority == pb->priority)
	{
		return pb->iteration - pa->iteration;
	}

	return pa->priority - pb->priority;
}