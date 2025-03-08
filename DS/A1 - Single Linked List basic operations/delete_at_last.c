#include "sll.h"

int sl_delete_last(Slist **head)
{
  if(*head == NULL)
    return FAILURE;
 Slist *temp = *head;
 Slist *prev = NULL;
 if(temp->link == NULL)
 {
   free(temp);
   *head = NULL;
    return SUCCESS;
 }

 while(temp->link != NULL)
 {
    prev = temp;
    temp = temp->link;
 }
 free(temp);
 prev->link = NULL;
 return SUCCESS;
}
