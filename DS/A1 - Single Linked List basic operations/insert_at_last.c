#include "sll.h"

int insert_at_last(Slist **head, data_t data)
{
	
	Slist *new = malloc(sizeof(Slist));
	if(new == NULL)
		return FAILURE;
	new->data = data;
	new->link = NULL;

	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	Slist *temp = *head;
	while(temp->link != NULL)
	{
		temp = temp->link;
	}
	temp->link = new;
	return SUCCESS;
}
