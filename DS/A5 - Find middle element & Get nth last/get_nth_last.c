#include "sll.h"
/* Function to get the nth node from the last of a linked list*/
int find_nth_last(Slist *head, int pos, int *data) 
{
   if(head == NULL)
      return LIST_EMPTY;
   Slist *fast = head;
   Slist *slow = head;
   if(pos == 0)
       return FAILURE;
   while(fast != NULL)
   {
       if(pos != 0)
       {
	   pos--;
	   fast = fast->link;
       }
       else
       {
	   slow = slow->link;
	   fast = fast->link;
       }
   }
   if(pos != 0)
       return FAILURE;
   else
   {
       *data = slow->data;
       return SUCCESS;
   }

} 
