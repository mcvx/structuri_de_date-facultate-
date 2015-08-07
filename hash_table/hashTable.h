/* CRETU George Alexandru - 316CB */

#pragma once

#include <stdlib.h>
#include "list.h"

typedef struct
{
	void *key;
	void *value;
} TPair;

typedef struct
{
	int N;		// Numarul de bucket-uri
	TList* v;	// Vectorul de bucket-uri
} THashTable;

/* ------------------------ Functii interne ale structurii hashTable ------------------------ */

// Functia de hash - implementarea difera in functie de tipul cheilor
int __hashTable_hash(void *key, int N);

// Functia de comparare a cheilor - implementarea difera in functie de tipul cheilor
int __hashTable_compareKeys(void *keyA, void *keyB);



/* ------------------------ Functii externe ale structurii hashTable ------------------------ */

// Creeaza un nou tabel de dispersie cu N bucket-uri
THashTable* hashTable_new(int N);

// Distruge un tabel de dispersie
// Functia <freePair> elibereaza memoria utilizata de elementele de tip TPair
void hashTable_destroy(THashTable **ht, TFreeInfo freePair);

// Insereaza un nou element in tabel
int hashTable_insert(THashTable *ht, void *key, size_t keySize, void *value, size_t valueSize);

// Sterge un element din tabel
// Functia <freePair> elibereaza memoria utilizata de elementul de tip TPair
int hashTable_remove(THashTable *ht, void *key, TFreeInfo freePair);

// Returneaza valoarea ce are ca pereche cheia <key>
void* hashTable_value(THashTable *ht, void *key);

// Returneaza 1 daca in tabel exista cheia <key> sau 0 in caz contrar
int hashTable_hasKey(THashTable *ht, void *key);

// Afiseaza toate perechile din tabel
// Functia <print_elem> este folosita pentru afisarea unui element de tip TPair
void hashTable_print(THashTable *ht, TFPrintElem print_elem);

// Afiseaza toate perechile bucket-ului <bucket>
// Functia <print_elem> este folosita pentru afisarea unui element de tip TPair
void hashTable_printBucket(THashTable *ht, int bucket, TFPrintElem print_elem);