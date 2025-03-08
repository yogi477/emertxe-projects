#include "dll.h"

int dl_delete_first(Dlist **head, Dlist **tail)
{

if(*head == NULL)
	return FAILURE;
Dlist *temp = NULL;
if(*head != *tail)
{
temp = *head;
*head = temp->next;
(*head)->prev = NULL;
free(temp);
return SUCCESS;
}
else
{
free(*head);
*head = *tail = NULL;
return SUCCESS;
}
}
