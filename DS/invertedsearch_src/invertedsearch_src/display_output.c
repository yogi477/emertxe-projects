/***************************************************************************************************************************************************
*Author         :Emertxe(http://www.emertxe.com)
*Date           :Mon 22 May 2017 16:06:15 IST
*File           :display_output.c
*Title          :To display  the results.
*Description    :When all the words are searched the ouput list is formed. In this the file with max count
		:(representing maximum word match ) can be selected and displayed. For advanced searched,
		:(weightage of words stored in database linkedlist) can also be used. So the results will be more
		:accurate.
****************************************************************************************************************************************************/
#include "inverted_search.h"

void display_output(hashtable *hash)
{
	int flag = 0;
	for (int i = 0; i < 28; i++)
	{
		if(hash[i].link != NULL)
		{
			main_node *temp = hash[i].link;
			while (temp != NULL)
			{
				flag = 1;
				printf("\e[32m[%d] ",hash[i].index); //printing main node
				printf("[ %s ] ",temp->word);
				printf("%d ",temp->filecount);
				sub_node *temp_sub = temp->sublink;
				while (temp_sub != NULL)
				{
					printf("file/s: File : %s ",temp_sub->filename); //printing subnode
					printf("%d \e[0m",temp_sub->wordcount);
					temp_sub = temp_sub->sublink;
				}
				temp = temp->mainlink;
				printf("\n");
			}
		}
	}
	if(flag == 0)
	{
		printf("\e[31mHashtable is empty\e[0m\n");
		return;
	}
}
