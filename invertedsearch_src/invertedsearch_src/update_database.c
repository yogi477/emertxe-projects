
#include "inverted_search.h"

void create_indexlist(hashtable hash[],Slist **filelist,main_node **node,sub_node **subnode)
{
	/* Definition here */
	char str[20];
	printf("Enter the filename to update database: ");
	scanf(" %s",str);
	Slist *temp = *filelist;

	if(strstr(str,".txt") == NULL)
	{
		printf("\e[31m%s is not in .txt format\e[0m\n",str);
		return;
	}
	FILE *fptr = fopen(str,"r");
	if(fptr == NULL)
	{
		printf("\e[31m%s is Invalid file\e[0m\n",str);
		return;
	}
	char first = getc(fptr);
	fseek(fptr,-2,SEEK_END);
	char last = getc(fptr);
	if(first == '#' && last == '#')
	{
		extern int flag;
		if(flag == 1)
		{
			printf("\e[31mDatabase already created\e[0m\n");
			return;
		}
		rewind(fptr);
		//read from database file
		int index,filecount,wordcount;
		char str[20],filename[20];
		while (fscanf(fptr,"#%d;%[^;];%d;%[^;];%d;#%*[\n]",&index,str,&filecount,filename,&wordcount) == 5)
		{
			insert_at_last(filelist,filename);
			create_nodes_update(str,filename,&hash[index].link);
		}
		flag = 1;
		printf("\e[32mDatabase update successful\e[0m\n");
	}
	else if(strstr(str,".txt") != NULL)
	{
		while (temp != NULL)
		{
		if(strcmp(str,temp->filename) == 0)
		{
			printf("\e[31m%s is already present update is not possible\e[0m\n",str);
			return;
		}
		else
			temp = temp->filelink;
		}
		//create database
		sl_delete_list(filelist);
		insert_at_last(filelist,str);
		extern int flag;
		flag = 0;
		create_database(filelist,hash,node,subnode);
	}
	else
	{
		printf("\e[31m %s is not database file\e[0m\n",str);
		return;
	}
	
	
}

