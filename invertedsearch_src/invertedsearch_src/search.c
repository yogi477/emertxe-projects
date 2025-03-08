/***************************************************************************************************************************************************
*Author         :Emertxe(http://www.emertxe.com)
*Date           :Mon 22 May 2017 15:56:15 IST
*File           :search.c
*Title          :To search the words.
*Description    :Each word is now used to search in the linkedlist. The word has to be compared with
		:each word in the linked list. When found, the file details can be retrieved. Since the
		:linkedlist is in sorted order, the complexity of searching the word in the complete list
		:can be avoided. While string comparison, if the word in linkedlist is greater than the
		:word to be search, it shows the word doesnt exists in the list,
****************************************************************************************************************************************************/
#include "inverted_search.h"

int search (hashtable *hash)
{
	/* Definition here */
	char *str = input_from_user();
	int flag = 0,index;
	if(str == NULL)
	{
		printf("Give the word to search\n");
		return 1;
	}
	if(isupper(str[0]))
		index = str[0] - 'A';
	else if(islower(str[0]))
		index = str[0] - 'a';
	else if(isdigit(str[0]))
		index = 26;
	else 	index = 27;
	main_node *mnode = hash[index].link;
		while( mnode!= NULL)
		{
			if(strcmp(str,mnode->word) == 0)
			{
				flag = 1;
				printf("\e[32mWord %s is present in %d file/s\n",mnode->word,mnode->filecount); //main node content
				sub_node *temp_sub = mnode->sublink;
				while (temp_sub != NULL)
				{
					printf("In File : %s %d time/s\e[0m\n",temp_sub->filename,temp_sub->wordcount);  //main node content
					temp_sub = temp_sub->sublink;
				}
				break;
			}
			else 
			{
				mnode = mnode->mainlink;
			}
		}
	if(flag == 0)
	{
		printf("\e[31mThe word doesnt exists in the list\e[0m\n");
		return 1;
	}

}
																				