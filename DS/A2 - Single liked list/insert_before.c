#include "sll.h"

int sl_insert_before(Slist **head, data_t g_data, data_t ndata)
{
	if(*head == NULL)
		return LIST_EMPTY;
	Slist *temp = *head;

	Slist *new = malloc(sizeof(Slist));
	if(new == NULL)
		return FAILURE;
	new->data = ndata;
	new->link = NULL;

	if(temp->data == g_data)
	{
		new->link = temp;
		*head = new;
		return SUCCESS;
	}
	Slist *ptr = NULL;
	while(temp->link != NULL)
	{
		ptr = temp->link;
		if(ptr->data == g_data)
		{
			new->link = ptr;
			temp->link = new;
			return SUCCESS;
		}
		else
			temp = temp->link;
	}
	return DATA_NOT_FOUND;
}
