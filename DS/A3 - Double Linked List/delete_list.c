#include "dll.h"

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
	return FAILURE;
    Dlist *temp = *head;
    Dlist *next = NULL;
    while(temp != NULL)
    {
	next = temp->next;
	free(temp);
	temp = next;
    }
    *head = *tail = NULL;
    return SUCCESS;
}
