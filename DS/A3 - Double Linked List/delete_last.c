#include "dll.h"

int dl_delete_last(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
	return FAILURE;
    Dlist *temp = *tail;
    if(*head != *tail)
    {
	*tail = temp->prev;
	(*tail)->next = NULL;
	free(temp);
	return SUCCESS;
    }
    else
    {
	free(temp);
	*head = *tail = NULL;
    }
}
