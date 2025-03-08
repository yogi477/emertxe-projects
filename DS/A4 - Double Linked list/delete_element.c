#include "dll.h"

int dl_delete_element(Dlist **head, Dlist **tail, int data)
{
    if(*head == NULL)
	return LIST_EMPTY;
    Dlist *temp = *head;
    while(temp != NULL)
    {
	if(temp->data == data && *head == *tail)
	{
	    free(temp);
	    *head = NULL;
	    *tail = NULL;
	    return SUCCESS;
	}
	else if(temp->data == data && temp->prev == NULL)
	{
	    *head = temp->next;
	    temp->next->prev = NULL;
	    free(temp);
	    return SUCCESS;
	}
	else if(temp->data == data)
	{
	    if(temp->next == NULL)
	    {
		*tail = temp->prev;
		temp->prev->next = NULL;
		free(temp);
	    	return SUCCESS;
	    }
	    else
	    {
		temp->prev->next = temp->next;
	    	temp->next->prev = temp->prev;
	    	free(temp);
	    	return SUCCESS;
	    }
		
	}
	else 
	    temp = temp->next;
    }
    return DATA_NOT_FOUND;
}
