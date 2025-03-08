#include"inverted_search.h"

int openfiles(char *filename)
{
    FILE *ptr = fopen(filename,"r");
    if(ptr == NULL)
    {
        printf("\e[31mERROR in opening %s\e[0m\n",filename);
        return 1;
    }
    return 0;
}
//validation function
int validation(int argc,char *argv[],Slist **head)
{
    if (argc <= 1)
    {
        printf("\e[31mInsufficient arguments\e[0m\n");
        return FAILURE;
    }
    printf("\n");
    for(int i=1;i<argc;i++)
    {
        if(strstr(argv[i],".txt") == NULL)
        {
            printf("\e[31m%s is not .txt file\e[0m\n",argv[i]);
            continue;
        }
        else 
        {
            insert_at_last(head,argv[i]);
            printf("\e[32mSuccessful: Inserting filename : %s into file linked list\e[0m\n",argv[i]);
        }
        
        
    }
    return SUCCESS;
}
//function to initialze hashtable in beginnimg
void initialize_hashtable(hashtable arr[])
{
    for (int i = 0; i < 28; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }
    
}
//node creation function
int create_nodes(Slist *temp,FILE *ptr,char *str,main_node **hash_link)
{
    if(*hash_link == NULL)
    {
        //mainnode creation
        main_node *newmain = malloc(sizeof(main_node));
        if(newmain == NULL)
        {
            return FAILURE;
        }
        sub_node *newsub = malloc(sizeof(sub_node));
        if(newsub == NULL)
        {
            return FAILURE;
        }
        newmain->filecount = 1;
        strcpy(newmain->word,str);
        newmain->mainlink = NULL;
        //subnode creation
        newsub->wordcount = 1;
        strcpy(newsub->filename,temp->filename);
        newsub->sublink = NULL;
        //establish link
        newmain->sublink = newsub;
        *hash_link = newmain;
        memset(str,'\0',strlen(str));
    }
    else
    {
        //creation of node if already node present
        main_node *maintemp = *hash_link;
        main_node *mainprev = NULL;
        while (maintemp != NULL)
        {
            if(strcmp(str,maintemp->word) == 0)
            {
                sub_node *subtemp = maintemp->sublink;
                sub_node *prevsub = NULL;
                while (subtemp != NULL)
                {
                    if(strcmp(temp->filename,subtemp->filename) == 0)
                    {
                        subtemp->wordcount++;
                        return SUCCESS;
                    }
                    prevsub = subtemp;
                    subtemp = subtemp->sublink;
                }
                sub_node *newsub1 = malloc(sizeof(sub_node));
                if(newsub1 == NULL)
                {
                    return FAILURE;
                }
                newsub1->wordcount = 1;
                strcpy(newsub1->filename,temp->filename);
                newsub1->sublink = NULL;
                prevsub->sublink = newsub1;
                maintemp->filecount++;
                return SUCCESS;
            }
            mainprev = maintemp;
            maintemp = maintemp->mainlink;
        }
        main_node *newmain1 = malloc(sizeof(main_node));
        if (newmain1 == NULL)
        {
            return FAILURE;
        }
        newmain1->filecount = 1;
        strcpy(newmain1->word,str);
        newmain1->mainlink = NULL;
        sub_node *newsub2 = malloc(sizeof(sub_node));
        if(newsub2 == NULL)
        {
            return FAILURE;

        }
        newsub2->wordcount = 1;
        strcpy(newsub2->filename,temp->filename);
        newsub2->sublink = NULL;
        newmain1->sublink = newsub2;
        mainprev->mainlink = newmain1;
        return SUCCESS;
    }
}
//file list deletion
int sl_delete_list(Slist **head)
{
	if(*head == NULL)
	   return 1;
	Slist *temp = *head;
	Slist *prev = NULL;
	while( temp != NULL)
	{
	  prev = temp;
	  temp = temp->filelink;
	  free(prev);
	}
	*head = NULL;
	return 0;
}
//node creation in update database
int create_nodes_update(char *str,char *filename,main_node **hash_link)
{
    if(*hash_link == NULL)
    {
        //mainnode creation
        main_node *newmain = malloc(sizeof(main_node));
        if(newmain == NULL)
        {
            return FAILURE;
        }
        sub_node *newsub = malloc(sizeof(sub_node));
        if(newsub == NULL)
        {
            return FAILURE;
        }
        newmain->filecount = 1;
        strcpy(newmain->word,str);
        newmain->mainlink = NULL;
        //subnode creation
        newsub->wordcount = 1;
        strcpy(newsub->filename,filename);
        newsub->sublink = NULL;
        //establish link
        newmain->sublink = newsub;
        *hash_link = newmain;
        memset(str,'\0',strlen(str));
    }
    else
    {
        //
        main_node *maintemp = *hash_link;
        main_node *mainprev = NULL;
        while (maintemp != NULL)
        {
            if(strcmp(str,maintemp->word) == 0)
            {
                sub_node *subtemp = maintemp->sublink;
                sub_node *prevsub = NULL;
                while (subtemp != NULL)
                {
                    if(strcmp(filename,subtemp->filename) == 0)
                    {
                        subtemp->wordcount++;
                        return SUCCESS;
                    }
                    prevsub = subtemp;
                    subtemp = subtemp->sublink;
                }
                sub_node *newsub1 = malloc(sizeof(sub_node));
                if(newsub1 == NULL)
                {
                    return FAILURE;
                }
                newsub1->wordcount = 1;
                strcpy(newsub1->filename,filename);
                newsub1->sublink = NULL;
                prevsub->sublink = newsub1;
                maintemp->filecount++;
                return SUCCESS;
            }
            mainprev = maintemp;
            maintemp = maintemp->mainlink;
        }
        main_node *newmain1 = malloc(sizeof(main_node));
        if (newmain1 == NULL)
        {
            return FAILURE;
        }
        newmain1->filecount = 1;
        strcpy(newmain1->word,str);
        newmain1->mainlink = NULL;
        sub_node *newsub2 = malloc(sizeof(sub_node));
        if(newsub2 == NULL)
        {
            return FAILURE;

        }
        newsub2->wordcount = 1;
        strcpy(newsub2->filename,filename);
        newsub2->sublink = NULL;
        newmain1->sublink = newsub2;
        mainprev->mainlink = newmain1;
        return SUCCESS;
    }
}