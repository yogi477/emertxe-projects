#include"hash.h"

int destroy_HT(hash_t *arr, int size)
{
    
    for(int i = 0;i < size ;i++)
    {
        
            hash_t *temp = arr[i].link;
            hash_t *prev = NULL;
            while(temp != NULL)
            {
                prev = temp->link;
                free(temp);
                temp = prev;
                
            }
            arr[i].link = NULL;
            arr[i].value = -1;
        
    }
    return SUCCESS;
}