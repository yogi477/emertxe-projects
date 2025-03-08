/***************************************************************************************************************************************************
*Author		:Emertxe(http://www.emertxe.com)
*Date		:Mon 22 May 2017 14:00:05 IST
*File		:main.c
*Title		:Driver function
*Description	:This function acts like the driver function for the project inverted search
****************************************************************************************************************************************************/
/*
Name : yogesh k (24021B)
Date : 5/3/2025
Description : Inverted search project
Input: ./a.out file1.txt file2.txt
Output: Successful: Inserting filename : file1.txt into file linked list    

		Select your choice among the following options:
		1. Create DataBase
		2. Display DataBase
		3. Update DataBase
		4. Search DataBase
		5. Save DataBase
		6. Exit
		Enter your choice : 1
		Successfull : creation of Database for file: file1.txt
		Enter your Choice:

*/
#include "inverted_search.h"

Slist *list = NULL;
sub_node *sub = NULL;
main_node *main_n = NULL;
hashtable hash[28];
int flag = 0;
int main(int argc, char *argv[])
{
	/* Define the main function here */
	int choice;
	char ch;
	if(validation(argc,argv,&list) == FAILURE)
			return 1;
	initialize_hashtable(hash);
	do
	{
		printf("Select your choice among the following options:\n1. Create Database\n2. Display Data\n3. Update DataBase\n4. Search\n5. Save Database\n6. Exit\n");
		printf("Enter your Choice: ");
		scanf("%d",&choice);
		switch (choice)
		{
		case 1:
			create_database(&list,hash,&main_n,&sub);
			break;
		case 2:
			display_output(hash);
			break;
		case 3:
			create_indexlist(hash,&list,&main_n,&sub);
			break;
		case 4:
			search(hash);
			break;
		case 5:
			write_databasefile(hash);
			break;
		case 6:
			return 0;
		default:
			break;
		}
	} while (choice < 7);	
}

