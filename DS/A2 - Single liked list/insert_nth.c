#include "sll.h"

int sl_insert_nth(Slist **head, data_t data, data_t n)
{
	if(*head == NULL && n != 1)
		return LIST_EMPTY;
	Slist *temp = *head;
	Slist *new = malloc(sizeof(Slist));
	if(new == NULL)
		return FAILURE;
	new->data = data;
	new->link = NULL;
	int count = 1;
	if(count == n)
	{
		new->link = *head;
		*head = new;
		return SUCCESS;
	}
	Slist *prev = NULL;
	while(temp!= NULL)
	{
		prev = temp->link;
		count++;
		if(count == n)
		{
			new->link = temp->link;
			temp->link = new;
			return SUCCESS;
		}
		else
			temp = temp->link;
	}
	return POSITION_NOT_FOUND;
}
