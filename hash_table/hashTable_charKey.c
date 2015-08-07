/* CRETU Alexandru - 316CB */

#include "hashTable.h"

#include <stdio.h>
#include <string.h>

/* Functii specifice implementarii cu chei de tip sir de caratere */

int __hashTable_hash(void *key, int N)
{
	int i, len, s;
	char *keyString = (char*) key;

	len = strlen(key);
	s = 0;

	for (i = 0; i < len; i++)
	{
		s += keyString[i];
	}

	return s % N;
}

int __hashTable_compareKeys(void *keyA, void *keyB)
{
	return strcmp(keyA, keyB);
}



/* ---------------------- Functii generice ---------------------- */

THashTable* hashTable_new(int N)
{
	THashTable *ht = calloc(1, sizeof(THashTable));
	if (!ht)
	{
		return NULL;
	}

	ht->N = N;
	ht->v = calloc(N, sizeof(TList));
	if (!ht->v)
	{
		free(ht);
		return NULL;
	}

	return ht;
}

void hashTable_destroy(THashTable **ht, TFreeInfo freePair)
{
	int i;
	TList l;

	for (i = 0; i < (*ht)->N; i++)
	{
	    l = (*ht)->v[i];
	    list_destroy(&l, freePair);
	}

	free((*ht)->v);
	free(*ht);

	*ht = NULL;
}

int hashTable_insert(THashTable *ht, void *key, size_t keySize, void *value, size_t valueSize)
{
	int p = __hashTable_hash(key, ht->N);
	TList *l = &ht->v[p];

	int ok = -1;
	while (*l != NULL && (ok = __hashTable_compareKeys(((TPair*)(*l)->info)->key, key)) < 0)
	{
		l = &(*l)->next;
	}

	if (ok == 0)
	{
		return 0;
	}

	TPair *pair = calloc(1, sizeof(TPair));
	if (!pair)
	{
		return -1;
	}

	pair->key = calloc(1, keySize);
	if (!pair->key)
	{
		free(pair);
		return -1;
	}

	pair->value = calloc(1, valueSize);
	if (!pair->value)
	{
		free(pair->key);
		free(pair);
		return -1;
	}

	memcpy(pair->key, key, keySize);
	memcpy(pair->value, value, valueSize);

	TList aux = calloc(1, sizeof(TCell));
	aux->next = *l;
	aux->info = pair;
	*l = aux;

	return 1;
}

int hashTable_remove(THashTable *ht, void *key, TFreeInfo freePair)
{
	int p = __hashTable_hash(key, ht->N);
	TList *l = &ht->v[p];

	int ok = -1;
	while (*l != NULL && (ok = __hashTable_compareKeys(((TPair*)(*l)->info)->key, key)) < 0)
	{
		l = &(*l)->next;
	}

	if (ok == 0)
	{
		list_remove(l, freePair);
		return 1;
	}

	return 0;
}

void* hashTable_value(THashTable *ht, void *key)
{
	int p = __hashTable_hash(key, ht->N);
	TList *l = &ht->v[p];

	int ok = -1;
	while (*l != NULL && (ok = __hashTable_compareKeys(((TPair*)(*l)->info)->key, key)) < 0)
	{
		l = &(*l)->next;
	}

	if (ok == 0)
	{
		return ((TPair*)(*l)->info)->value;
	}

	return NULL;
}

int hashTable_hasKey(THashTable *ht, void *key)
{
	int p = __hashTable_hash(key, ht->N);
	TList *l = &ht->v[p];

	int ok = -1;
	while (*l != NULL && (ok = __hashTable_compareKeys(((TPair*)(*l)->info)->key, key)) < 0)
	{
		l = &(*l)->next;
	}

	return (ok == 0);
}

void hashTable_print(THashTable *ht, TFPrintElem print_elem)
{
	int i;
	TList l;

	for (i = 0; i < ht->N; i++)
	{
		l = ht->v[i];

		if (!l)
		{
			continue;
		}

		printf("%d: ", i);
		list_print(&l, print_elem);
	}
}

void hashTable_printBucket(THashTable *ht, int bucket, TFPrintElem print_elem)
{
	if (bucket >= ht->N)
	{
		return;
	}

	TList *l = &ht->v[bucket];
	list_print(l, print_elem);
}