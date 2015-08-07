/* CRETU George Alexandru - 316CB */

#include "list.h"

#include <stdio.h>
#include <string.h>

int list_insert(TList *list, void *info, size_t infoSize)
{
    TList aux = calloc(1, sizeof(TCell));
    if (!aux)
    {
        return 0;
    }

    aux->info = calloc(1, infoSize);
    if (!aux->info)    
    {
        free(aux);
        return 0;
    }

    memcpy(aux->info, info, infoSize);
    aux->next = *list;
    *list = aux;

    return 1;
}

void list_remove(TList *elem, TFreeInfo freeInfo)
{
    TList aux = *elem;

    if (!aux)
    {
        return;
    }

    freeInfo(aux->info);
    *elem = aux->next;
    free(aux);
}

void list_destroy(TList *list, TFreeInfo freeInfo)
{
    while (*list != NULL)
    {
        list_remove(list, freeInfo);
    }
}

size_t list_length(TList *list)
{
    size_t lg = 0;
    TList p = *list;

    for ( ; p != NULL; p = p->next)
    {
        lg++;
    }

    return lg;
}

void list_print(TList *list, TFPrintElem print_elem)
{ 
    if (!*list)
    {
        printf("VIDA\n");
        return;
    }

    for ( ; *list != NULL; list = &(*list)->next)
    {
        print_elem((*list)->info);
    }
    
    printf("\n");
}