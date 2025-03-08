#include "dll.h"

int dl_insert_after(Dlist **head, Dlist **tail, int gdata, int ndata)
{
    if(*head == NULL)
	return LIST_EMPTY;
    Dlist *temp = *head;
    while(temp != NULL)
    {
	if(temp->data != gdata)
	    temp = temp->next;
	else
	{
    	Dlist *new = malloc(sizeof(Dlist));
	if(new == NULL)
	    return FAILURE;
	new->data = ndata;
	new->prev = temp;
	new->next = temp->next;
	temp->next = new;
	if(temp != *tail)
	{
	    new->next->prev = new;
	    return SUCCESS;
	}
	else
	{
	    *tail = new;
	     return SUCCESS;
	}
	}
    }
return DATA_NOT_FOUND;
}
