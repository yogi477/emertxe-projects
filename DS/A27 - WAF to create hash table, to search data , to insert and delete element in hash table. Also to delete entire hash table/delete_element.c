#include"hash.h"

int delete_element(hash_t *arr, int data, int size)
{
    if(data == -1)
        return DATA_NOT_FOUND;
    int index = data % size;
    if(arr[index].index == index)
    {
        if(arr[index].value == data && arr[index].link == NULL)
        {
            arr[index].value = -1;
            return SUCCESS;
        }
        else if(arr[index].value == data && arr[index].link != NULL)
        {
            hash_t *temp = arr[index].link;
            arr[index].value = temp->value;
            arr[index].link = temp->link;
            free(temp);
            return SUCCESS;
        }
        else if(arr[index].value != data && arr[index].link != NULL)
        {
            hash_t *temp = arr[index].link;
            hash_t *prev = &arr[index];
            while(temp != NULL)
            {
                if(temp->value == data)
                {
                   prev->link = temp->link;
                   hash_t *dup = temp;
                   free(dup);
                   return SUCCESS;
                }
                prev = temp;
                temp = temp->link;
                
            }
            return DATA_NOT_FOUND;
        }
        else if(arr[index].value != data && arr[index].link == NULL)
        {
            return DATA_NOT_FOUND;
        }
    }
    
    
}