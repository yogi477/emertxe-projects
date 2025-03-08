#include "apc.h"

int main()
{
	/* Declare the pointers */
      
	Dlist *head1=NULL, *tail1=NULL;
        Dlist *head2=NULL, *tail2=NULL; 
        Dlist *headR=NULL,*tailR=NULL;


	char operator=argv[2][0];


		switch (operator)
		{
			case '+':
                                digit_to_list(&head1,&tail1,&head2,&tail2,argv);
				/* call the function to perform the addition operation */
                                addition(&head1,&tail1,&head2,&tail2,&headR,&tailR);
				break;
			case '-':	
				/* call the function to perform the subtraction operation */
				break;
			case '*':	
				/* call the function to perform the multiplication operation */
				break;
			case '/':	
				/* call the function to perform the division operation */
				break;
			default:
				printf("Invalid Input:-( Try again...\n");
		}
	return 0;
}
