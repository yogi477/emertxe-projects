#include "dll.h"
int dl_insert_before(Dlist **head, Dlist **tail, int gdata, int ndata)
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
	    new->prev = temp->prev;
	    new->next = temp;
	    temp->prev = new;
	    if(*head != *tail && new->prev != NULL)
		new->prev->next = new;
	    else
		*head = new;
	    return SUCCESS;
	}
    }
    return DATA_NOT_FOUND;
}
