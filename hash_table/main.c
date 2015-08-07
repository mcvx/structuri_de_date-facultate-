/* CRETU George Alexandru - 316CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"

// Functia de afisare a valorii unei perechi
void print_value_char(void *p)
{
	TPair *pair = p;
	printf("%s ", (char*)pair->value);
}

// Functia de eliberare a memoriei ocupate de o pereche
void free_pair(void *p)
{
	TPair *pair = p;
	free(pair->key);
	free(pair->value);
	free(pair);
}

int main(int argc, char *argv[])
{
	char command[32], key[128], value[16], *aux;
	int bucket, N;

	// Daca nu exista destule argumente la rularea programului, atunci opreste executia
	if (argc < 4)
	{
		return -1;
	}

	// Setarea numarului N de bucket-uri si a fisierelor de intrare/iesire
	N = strtol(argv[1], &aux, 10);
	freopen(argv[2], "r", stdin);
	freopen(argv[3], "w", stdout);

	// Creeaza un nou tabel de dispersie cu N bucket-uri
	THashTable *ht = hashTable_new(N);

	// Citeste si executa comenzile din fisierul de intrare
	while (fscanf(stdin, "%s", command) != EOF)
	{
		if (strcmp(command, "put") == 0)
		{
			fscanf(stdin, "%s", key);
			fscanf(stdin, "%s", value);

			hashTable_insert(ht, key, strlen(key) + 1, value, strlen(value) + 1);
		}
		else if (strcmp(command, "get") == 0)
		{
			fscanf(stdin, "%s", key);

			char *value = hashTable_value(ht, key);
			printf("%s\n", value ? value : "NULL");
		}
		else if (strcmp(command, "remove") == 0)
		{
			fscanf(stdin, "%s", key);

			hashTable_remove(ht, key, free_pair);
		}
		else if (strcmp(command, "find") == 0)
		{
			fscanf(stdin, "%s", key);

			printf("%s\n", hashTable_hasKey(ht, key) ? "True" : "False");
		}
		else if (strcmp(command, "print") == 0)
		{
			hashTable_print(ht, print_value_char);
		}
		else if (strcmp(command, "print_bucket") == 0)
		{
			fscanf(stdin, "%d", &bucket);

			hashTable_printBucket(ht, bucket, print_value_char);
		}
	}

	// Distruge tabelul de dispersie
	hashTable_destroy(&ht, free_pair);

	return 0;
}