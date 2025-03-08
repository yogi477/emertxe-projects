/***************************************************************************************************************************************************
*Author         :Emertxe(http://www.emertxe.com)
*Date           :Mon 22 May 2017 14:04:05 IST
*File           :create_database.c
*Title          :To create the database
*Description    :The list of the files can be provided by storing all the file names in another file, FileList the names of the files which 
		:are to be documented are provided by this file. When a file is added or removed, FileList is changed accordingly.
		:So read the file names and start indexing.
****************************************************************************************************************************************************/
#include "inverted_search.h"

int create_database(Slist **filelist,hashtable hash[],main_node **node,sub_node **subnode)
{
	/* Definition here */
	extern int flag;
	if(flag == 1)
	{
		printf("\e[31mDatabase already created\e[0m\n");
		return 1;
	}
	Slist *temp = *filelist;
	char str[20];
	int index;
	while (temp != NULL)
	{
		FILE *ptr = fopen(temp->filename,"r");
		if(ptr == NULL)
		{
			printf("\e[31m%s is Invalid file\e[0m\n",temp->filename);
			return 1;
		}
		if(fgetc(ptr) == EOF)
		{
			printf("\e[31m%s is Empty\e[0m\n",temp->filename);
			temp = temp->filelink;
			continue;
		}
		else
		{
			rewind(ptr);
			while (fscanf(ptr,"%s",str) == 1)
			{
				if(isupper(str[0]))
				{
					index = str[0] - 'A';
					create_nodes(temp,ptr,str,&hash[index].link);
				}
				else if(islower(str[0]))
				{
					index = str[0] - 'a';
					create_nodes(temp,ptr,str,&hash[index].link);
				}
				else if(isdigit(str[0]))
				{
					index = 26;
					create_nodes(temp,ptr,str,&hash[index].link);
				}
				else
				{
					index = 27;
					create_nodes(temp,ptr,str,&hash[index].link);

				}
			}
			
		}
		printf("\e[32mSuccessfull : creation of Database for file: %s\e[0m\n",temp->filename);
		temp = temp->filelink;
	}
	flag = 1;
	return SUCCESS;

}
