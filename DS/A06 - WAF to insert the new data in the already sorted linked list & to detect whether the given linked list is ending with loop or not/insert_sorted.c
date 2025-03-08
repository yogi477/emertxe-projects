#include "sll.h"

/* Function for insert the number in sorted linked list */
int insert_sorted( Slist **head, data_t data) 
{ 
    Slist *new = malloc(sizeof(Slist));
    if(new == NULL)
	return FAILURE;
    new->data = data;
    new->link = NULL;
    Slist *temp = *head;
    if(temp == NULL || temp->data > data)
    {
	new->link = temp;
	*head = new;
	return SUCCESS;
    }
    while(temp->link != NULL && temp->link->data  < data)
    {
	temp = temp->link;
    }
    new->link = temp->link;
    temp->link = new;
    return SUCCESS;
}

  
