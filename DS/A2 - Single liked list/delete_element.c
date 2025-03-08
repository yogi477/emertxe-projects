#include"sll.h"

int sl_delete_element(Slist **head, data_t data)
{
if(*head == NULL)
	return FAILURE;
Slist *temp = *head;
if(temp->data == data)
{
*head = temp->link;
free(temp);
return SUCCESS;
}
Slist *ptr = NULL;
while(temp != NULL)
{
ptr = temp->link;
if(ptr->data == data)
{
temp->link = ptr->link;
free(ptr);
return SUCCESS;
}
else
temp = temp->link;
}
return DATA_NOT_FOUND;
}

