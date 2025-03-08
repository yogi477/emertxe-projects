#include "sll.h"

/* Function to create the loop */
int create_loop(Slist **head, data_t data)
{
    if(*head == NULL)
	return LIST_EMPTY;
    Slist *temp = *head;
    Slist *ptr = NULL;
    while(temp != NULL)
    {
	if(temp->data == data && ptr == NULL)
	{
	    ptr = temp;
	}
	if(temp->link == NULL && ptr != NULL)
	{
	       temp->link = ptr;
	       return SUCCESS;
	}

	temp = temp->link;
    }
    return DATA_NOT_FOUND;
}
