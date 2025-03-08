#include"hash.h" 

int main()
{
	int size, data, choice, index;
	char opt;
	printf("Enter the size of arr: ");
	scanf("%d", &size);
	hash_t arr[size];
	create_HT(arr, size);
	
	printf("1. Insert data in HT\n2. Search data in HT\n3. Delete data from HT\n4. Destroy HT\n5. Display HT\n6. Exit\nEnter you choice : ");
	while(1)
	{
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("Enter the data: ");
				scanf("%d", &data);
				if(insert_HT(arr, data, size) == FAILURE)
				{
					printf("INFO : Insert data is Failure\n");
				}
				
				break;

			case 2:
				printf("Enter the data: ");
				scanf("%d", &data);
				if((search_HT(arr, data, size)) == DATA_NOT_FOUND)
				{
					printf("INFO : Data not found\n");
				}
				else
				{
					printf("INFO : %d is found at the index %d\n", data, data % size);
				}
				break;

			case 3:
				printf("Enter the data: ");
				scanf("%d", &data);
				if(delete_element(arr, data, size) == DATA_NOT_FOUND)
				{
					printf("INFO : Data is not found\n");
				}
				else
				{
					printf("INFO : %d is deleted successfully\n",data);
				}
				break;

			case 4:
				if(destroy_HT(arr,size) == SUCCESS)
				{
					printf("INFO: Hashtable deleted successfully\n");
				}
				else
				{
					printf("INFO: Delete hashtable is Failure\n");
				}
				break;

			case 5:
				display_HT(arr, size);
				break;
			case 6:
				return SUCCESS;

			default:
				printf("Invalid input\n");
		}
	}
}