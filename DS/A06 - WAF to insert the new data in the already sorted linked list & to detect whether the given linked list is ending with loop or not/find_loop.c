#include "sll.h"

/* Function for finding the loop in the link */
int find_loop(Slist *head)
{
    if(head == NULL)
	return LIST_EMPTY;
    Slist *fast = head,*slow = head;
    while(fast != NULL && fast->link != NULL)
    {
	slow = slow->link;
	fast = fast->link->link;
	if(fast == slow)
	    return SUCCESS;
    }
    return LOOP_NOT_FOUND;
}
