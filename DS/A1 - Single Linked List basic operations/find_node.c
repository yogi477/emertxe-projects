#include "sll.h"

int find_node(Slist *head, data_t data)
{
if(head == NULL)
 return FAILURE;
Slist *temp = head;
int count = 1;
while(temp != NULL)
{
if(temp->data == data)
  return count;
count++;
temp = temp->link;
}
return FAILURE;
}
