#include "inverted_search.h"
int insert_at_last(Slist **head, char *data)
{
	Slist *temp1 = *head;
	while(temp1 != NULL)
	{
		if(strcmp(temp1->filename,data) == 0)
		{
			return 1;
		}
		temp1 = temp1->filelink;
	}
	
	Slist *new = malloc(sizeof(Slist));
	if(new == NULL)
		return 0;
	strcpy(new->filename,data);
	new->filelink = NULL;

	if(*head == NULL)
	{
		*head = new;
		return 1;
	}
	Slist *temp = *head;
	while(temp->filelink != NULL)
	{
		temp = temp->filelink;
	}
	temp->filelink = new;
	return 1;
}
void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s ", head->filename);
		    head = head->filelink;
	    }

	    printf("\n");
    }
}