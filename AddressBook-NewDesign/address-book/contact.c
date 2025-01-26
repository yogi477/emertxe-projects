#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
	loadContactsFromFile(addressBook);
}

int name_validate(char *name)
{
	//STEP1: Fetch one by one character till null character
	int i = 0;
	while(name[i] != '\0')
	{
		if(name[i]!=' ')
		{
		if(!(isalpha(name[i])))
		{
			return 1;
			//STEP2: Check the character is alpahebet or not
			//Yes-> Move to next character, NO -> Stop the process
		}
		}
		i++;
	}
	return 0;
}
int unique_name(char *name,AddressBook *book)
{
	for (int i = 0; i < book->contactCount; i++)
	{
		if (strcmp(name,book->contacts[i].name) == 0)
		{
			return 1;
		}
		
	}
	return 0;
}
int number_validate(char *number)
{
	//STEP1: Fetch one by one character till null character
	int i = 0;
	while(number[i] != '\0')
	{
		if(!(isdigit(number[i])))
		{
			return 1;
			//STEP2: Check the character is alpahebet or not
			//Yes-> Move to next character, NO -> Stop the process
		}
		i++;
	}
	return 0;
}

int unique_number(char *number,AddressBook *book)
{
	for (int i = 0; i < book->contactCount; i++)
	{
		if (strcmp(number,book->contacts[i].phone) == 0)
		{
			return 1;
		}
		
	}
	return 0;
}
int unique_email(char *email,AddressBook *book)
{
	for (int i = 0; i < book->contactCount; i++)
	{
		if (strcmp(email,book->contacts[i].email) == 0)
		{
			return 1;
		}
		
	}
	return 0;
}

void createContact(AddressBook *addressBook)
{
	char name[20];
	
    //STEP1: Read a name from user
	printf("Enter the name: ");
	//__fpurge(STDIN);
	//getchar();
	scanf(" %[^\n]", name);


    //STEP2: Validate the name -> Alphabets
	while(name_validate(name) == 1)
	{
		printf("INFO: Name validation not done, Please enter valid name...\n");
		printf("Enter the name: ");
		scanf(" %[^\n]", name);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	while (unique_name(name,addressBook) == 1)
	{
		printf("INFO: Name already exists, Please enter valid name...\n");
		printf("Enter the name: ");
		scanf(" %[^\n]", name);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	char dup_name[30];
	strcpy(dup_name,name);
	//STEP3: Read a mobile number from user
	//STEP4: Validate the mobile number -> Digit & 10 Digits & unique
	//True -> Goto STEP5, False -> print error, Goto STEP3

	//STEP5: Read a email_id from user
	//STEP6: Validate the email_ID -> @gmail.com & unique
	//True -> Goto STEP7, False -> print error, Goto STEP5

	//STEP7: store into structure[contact_count]


	/* Define the logic to create a Contacts */
	char number[15];

	printf("Enter the mobile number: ");
	scanf(" %[^\n]", number);
	
	while(number_validate(number) == 1)
	{
		printf("INFO: Number validation not done, Please enter valid number...\n");
		printf("Enter the number: ");
		scanf(" %[^\n]", number);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	while (strlen(number) != 10)
	{
		printf("INFO: Number validation not done, Please enter 10 digits only...\n");
		printf("Enter the number: ");
		scanf(" %[^\n]", number);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	while (unique_number(number,addressBook) == 1)
	{
		printf("INFO: Number already exists, Please enter valid number...\n");
		printf("Enter the number: ");
		scanf(" %[^\n]", number);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	
	
	//Email logic
	char email[15];

	printf("Enter the Email_id: ");
	scanf(" %[^\n]", email);

	while (strstr(email,"@gmail.com") == NULL)
	{
		printf("INFO: Email validation not done, Please enter valid Email...\n");
		printf("Enter the Email_id: ");
		scanf(" %[^\n]", email);
	}
	
	while (unique_email(email,addressBook) == 1)
	{
		printf("INFO: Email already exists, Please enter valid Email...\n");
		printf("Enter the name: ");
		scanf(" %[^\n]", email);
		//True -> Goto STEP3, False -> print error, Goto STEP1
	}
	


	//for (int i = addressBook->contactCount; i < MAX_CONTACTS; i++)
	//{
		strcpy(addressBook->contacts[addressBook->contactCount].name ,dup_name);
		strcpy(addressBook->contacts[addressBook->contactCount].phone ,number);
		strcpy(addressBook->contacts[addressBook->contactCount].email ,email);
		addressBook->contactCount++;
		printf("\e[32m=== contact created successfully ===\e[0m\n");
		//break;
	//}
	
	
}



void searchContact(AddressBook *addressBook) 
{
	/* Define the logic for search */
	//STEP1: Print the menu Based on what searching
	//STEP2: Choose the menu
	repeat_search:
	int choice;
	printf("\n");
	printf("Choose any one details to search\n1.Name\n2.Mobile_no\n3.Email_id\n4.Exit\n");
	printf("Enter your choice: ");
	scanf(" %d",&choice);
	int flag = 0,flag1 = 0,flag2 = 0;
	
	//1 -> Name
	//Read the name
	//Search the extered name is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
	
	//2 -> Mobile_no
	//Read the mobile_no
	//Search the extered mobile_no is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	//3 -> Email_id
	//Read the mail_id
	//Search the extered mail_id is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	switch (choice)
	{
	case 1:
	while(flag == 0)
	{	char search_name[20];
		int index;
		printf("Enter the name to search: ");
		scanf(" %[^\n]", search_name);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_name,addressBook->contacts[i].name) == 0)
			{
				flag = 1;
				index = i;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
		 printf("\e[32m::: Details of this name :::\e[0m\n");
		 printf("Name:%s Mobile_no:%s Email_id:%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
		}
		else
		{
			printf("=== The name you entered is not present ===\n");
		}
	}
		break;
	
	case 2:
	while(flag1 == 0)
	{
		char search_mobile[20];
		int index1;
		printf("Enter the mobile_no to search: ");
		scanf(" %[^\n]", search_mobile);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_mobile,addressBook->contacts[i].phone) == 0)
			{
				flag1 = 1;
				index1 = i;
				break;
			}
			else
			{
				flag1 = 0;
			}
		}
		if (flag1 == 1)
		{
		 printf("\e[32m::: Details of this mobile_no :::\e[0m\n");
		 printf("Name:%s Mobile_no:%s Email_id:%s\n",addressBook->contacts[index1].name,addressBook->contacts[index1].phone,addressBook->contacts[index1].email);
		}
		else
		{
			printf("=== The mobile_no you entered is not present ===\n");
		}
	}
		break;
	
	case 3:
	while(flag2 == 0)
	{
		char search_email[20];
		int index2;
		printf("Enter the Email_id to search: ");
		scanf(" %[^\n]", search_email);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_email,addressBook->contacts[i].email) == 0)
			{
				flag2 = 1;
				index2 = i;
				break;
			}
			else
			{
				flag2 = 0;
			}
		}
		if (flag2 == 1)
		{
		 printf("\e[32m::: Details of this Email_id :::\e[0m\n");
		 printf("Name:%s Mobile_no:%s Email_id:%s\n",addressBook->contacts[index2].name,addressBook->contacts[index2].phone,addressBook->contacts[index2].email);
		
		}
		else
		{
			printf("=== The Email_id you entered is not present ===\n");

		}
	}	
		break;
		case 4:
		return ;
		default:
		printf("=== Invalid choice. Please try again ===\n");
		
	}
	goto repeat_search;

}
	

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int choice;
	printf("\n");
	printf("Choose which details you need to edit\n1.Name\n2.Mobile_no\n3.Email_id\n4.Exit\n");
	printf("Enter your choice: ");
	scanf(" %d",&choice);
	int flag = 0,flag1 = 0,flag2 = 0;
	
	//1 -> Name
	//Read the name
	//Search the extered name is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
	
	//2 -> Mobile_no
	//Read the mobile_no
	//Search the extered mobile_no is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	//3 -> Email_id
	//Read the mail_id
	//Search the extered mail_id is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
	switch (choice)
	{
	case 1:
	while(flag == 0)
	{	char search_name[20];
		int index;
		printf("Enter the name to edit: ");
		scanf(" %[^\n]", search_name);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_name,addressBook->contacts[i].name) == 0)
			{
				flag = 1;
				index = i;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			char new_name[20];
			printf("Enter the new name: ");
			scanf(" %[^\n]", new_name);
			while(name_validate(new_name) == 1)
			{
				printf("INFO: Name validation not done, Please enter valid name...\n");
				printf("Enter the new name: ");
				scanf(" %[^\n]", new_name);
				//True -> Goto STEP3, False -> print error, Goto STEP1
			}
			while (unique_name(new_name,addressBook) == 1)
			{
				printf("INFO: Name already exists, Please enter valid name...\n");
				printf("Enter the new name: ");
				scanf(" %[^\n]", new_name);
				//True -> Goto STEP3, False -> print error, Goto STEP1
			}
			strcpy(addressBook->contacts[index].name,new_name);
		 	printf("=== contact edited successfully ===\n");
		 
		 
			}
			else
			{
				printf("=== The name you entered is not present ===\n");
				
			}
	}
	
		break;
	case 2:
	while(flag1 == 0)
	{
		char search_mobile[20];
		int index1;
		printf("Enter the mobile_no to edit: ");
		scanf(" %[^\n]", search_mobile);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_mobile,addressBook->contacts[i].phone) == 0)
			{
				flag1 = 1;
				index1 = i;
				break;
			}
			else
			{
				flag1 = 0;
			}
		}
		if (flag1 == 1)
		{
		 	char new_number[20];
			printf("Enter the new number: ");
			scanf(" %[^\n]", new_number);
			while(number_validate(new_number) == 1)
			{
				printf("INFO: Number validation not done, Please enter valid number...\n");
				printf("Enter the new number: ");
				scanf(" %[^\n]", new_number);
				//True -> Goto STEP3, False -> print error, Goto STEP1
			}
			while (strlen(new_number) != 10)
			{
				printf("INFO: Number validation not done, Please enter 10 digits only...\n");
				printf("Enter the new number: ");
				scanf(" %[^\n]", new_number);
				//True -> Goto STEP3, False -> print error, Goto STEP1
			}
			while (unique_number(new_number,addressBook) == 1)
			{
				printf("INFO: Number already exists, Please enter valid number...\n");
				printf("Enter the new number: ");
				scanf(" %[^\n]", new_number);
				//True -> Goto STEP3, False -> print error, Goto STEP1
			}
			strcpy(addressBook->contacts[index1].phone,new_number);
		 	printf("\e[32mContacts saved successfully...\e[0m\n");
		}
		else
		{
			printf("=== The mobile_no you entered is not present ===\n");
		}
	}
		break;
		case 3:
		while(flag2 == 0)
		{
			char search_email[20];
			int index2;
			printf("Enter the Email_id to edit: ");
			scanf(" %[^\n]", search_email);
			for (int i = 0; i < addressBook->contactCount; i++)
			{
				if (strcmp(search_email,addressBook->contacts[i].email) == 0)
				{
					flag2 = 1;
					index2 = i;
					break;
				}
				else
				{
					flag2 = 0;
				}
			}
			if (flag2 == 1)
			{
				char new_email[20];
				printf("Enter the new Email_id: ");
				scanf(" %[^\n]", new_email);
				
				while (strstr(new_email,"@gmail.com") == NULL)
				{
					printf("INFO: Email validation not done, Please enter valid Email...\n");
					printf("Enter the new Email_id: ");
					scanf(" %[^\n]", new_email);
				}
				
				while (unique_email(new_email,addressBook) == 1)
				{
					printf("INFO: Email already exists, Please enter valid Email...\n");
					printf("Enter the new Email_id: ");
					scanf(" %[^\n]", new_email);
					//True -> Goto STEP3, False -> print error, Goto STEP1
				}
				strcpy(addressBook->contacts[index2].email,new_email);
		 		printf("\e[32mContacts saved successfully...\e[0m\n");
				
			}
			else
			{
				printf("=== The Email_id you entered is not present ===\n");

			}
		}
			break;
			case 4:
			return ;
			default:
			printf("=== Invalid choice. Please try again ===\n");
		
		}
		
	
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int choice;
	printf("\n");
	printf("Choose any one details to delete\n1.Name\n2.Mobile_no\n3.Email_id\n4.Exit\n");
	printf("Enter your choice: ");
	scanf(" %d",&choice);
	int flag = 0,flag1 = 0,flag2 = 0;
	
	//1 -> Name
	//Read the name
	//Search the extered name is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.
	
	//2 -> Mobile_no
	//Read the mobile_no
	//Search the extered mobile_no is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	//3 -> Email_id
	//Read the mail_id
	//Search the extered mail_id is present in the database or not
	//Yes -> Print the details about that contact, NO -> Print error, Goto STEP1.

	switch (choice)
	{
	case 1:
	while(flag == 0)
	{	char search_name[20];
		int index;
		printf("Enter the name to delete: ");
		scanf(" %[^\n]", search_name);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_name,addressBook->contacts[i].name) == 0)
			{
				flag = 1;
				index = i;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
		 int end = addressBook->contactCount-1;
		 int start = index;
		 for (int i = start; i < end; i++)
		 {
			strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
			strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
			strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
		}
		 
		 addressBook->contactCount--;
		 printf("\e[32mContacts deleted successfully...\e[0m\n");
		 
		 
		}
		else
		{
			printf("=== The name you entered is not present ===\n");
		}
	}
		break;
	
	case 2:
	while(flag1 == 0)
	{
		char search_mobile[20];
		int index1;
		printf("Enter the mobile_no to delete: ");
		scanf(" %[^\n]", search_mobile);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_mobile,addressBook->contacts[i].phone) == 0)
			{
				flag1 = 1;
				index1 = i;
				break;
			}
			else
			{
				flag1 = 0;
			}
		}
		if (flag1 == 1)
		{
		 int end = addressBook->contactCount-1;
		 int start = index1;
		 for (int i = start; i < end; i++)
		 {
			strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
			strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
			strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
		}
		 
		 addressBook->contactCount--;
		 printf("\e[32mContacts deleted successfully...\e[0m\n");
		 
		}
		else
		{
			printf("=== The mobile_no you entered is not present ===\n");
		}
	}
		break;
	
	case 3:
	while(flag2 == 0)
	{
		char search_email[20];
		int index2;
		printf("Enter the Email_id to delete: ");
		scanf(" %[^\n]", search_email);
		for (int i = 0; i < addressBook->contactCount; i++)
		{
			if (strcmp(search_email,addressBook->contacts[i].email) == 0)
			{
				flag2 = 1;
				index2 = i;
				break;
			}
			else
			{
				flag2 = 0;
			}
		}
		if (flag2 == 1)
		{
		 int end = addressBook->contactCount-1;
		 int start = index2;
		 for (int i = start; i < end; i++)
		 {
			strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
			strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
			strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
		}
		 
		 addressBook->contactCount--;
		 printf("\e[32mContacts deleted successfully...\e[0m\n");
		 
		}
		else
		{
			printf("=== The Email_id you entered is not present ===\n");

		}
	}	
		break;
		case 4:
		return ;
		default:
		printf("=== Invalid choice. Please try again ===\n");
	}
	

}

void listContacts(AddressBook *addressBook) 
{
	// Sort contacts based on the chosen criteria
	for (int i = 0; i < addressBook->contactCount; i++)
	{
		printf("Name:%s Mobile_no:%s Email_id:%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	
}
