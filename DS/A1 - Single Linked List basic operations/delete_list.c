#include "sll.h"

int sl_delete_list(Slist **head)
{
	if(*head == NULL)
	   return FAILURE;
	Slist *temp = *head;
	Slist *prev = NULL;
	while( temp != NULL)
	{
	  prev = temp;
	  temp = temp->link;
	  free(prev);
	}
	*head = NULL;
	return SUCCESS;
}
