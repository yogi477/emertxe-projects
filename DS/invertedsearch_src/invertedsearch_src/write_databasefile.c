/***************************************************************************************************************************************************
*Author         :Emertxe(http://www.emertxe.com)
*Date           :Mon 22 May 2017 14:20:10 IST
*File           :write_datbasefile.c
*Title          :Saves the details into the file
*Description    :All the files are opened and read. Words are listed. Now this list is to be stored. 
		:For this a new file “DatabaseFile” is created and opened in write mode. 
		:Now the words along with filelist (each node contents) are written to the Database file. 
		:In the file also the word should be written in sorted order. 
		:After that the file is closed properly.
****************************************************************************************************************************************************/
#include "inverted_search.h"

void write_databasefile(hashtable *hash)
{
	/* Definition here */
	char str[20];
	printf("Enter the filename to save database: ");
	scanf(" %s",str);
	if (strstr(str,".txt") == NULL)
	{
		printf("\e[31mEnter file name is .txt format\e[0m\n");
		return;
	}
	FILE *ptr = fopen(str,"w");
	if(ptr == NULL)
	{
		printf("\e[31m%s is Invalid file\e[0m\n",str);
		return;
	}
	int flag = 0;
	for (int i = 0; i < 28; i++)
	{
		if(hash[i].link != NULL)
		{
			main_node *temp = hash[i].link;
			while (temp != NULL)
			{
				flag = 1;
				fprintf(ptr,"#%d;",hash[i].index);  //writing to file mainnode content
				fprintf(ptr,"%s;",temp->word);
				fprintf(ptr,"%d;",temp->filecount);
				sub_node *temp_sub = temp->sublink;
				while (temp_sub != NULL)
				{
					fprintf(ptr,"%s;",temp_sub->filename); //writing to file subnode content
					fprintf(ptr,"%d;#",temp_sub->wordcount);
					temp_sub = temp_sub->sublink;
				}
				temp = temp->mainlink;
				fprintf(ptr,"\n");
			}
		}
	}
	if(flag == 0)
	{
		printf("\e[31mHashtable is empty\e[0m\n");
		return;
	}
	printf("\e[32mDatabase is saved\e[0m\n");
}

