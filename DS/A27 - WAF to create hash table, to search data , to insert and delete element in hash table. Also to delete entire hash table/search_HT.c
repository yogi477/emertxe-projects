#include"hash.h"

int search_HT(hash_t *arr, int data, int size)
{
    int index = data % size;
    if(arr[index].value == data)
    {
        return index;
    }
    else
    {
        if(arr[index].value == -1)
            return DATA_NOT_FOUND;
        else
        {
            if(arr[index].link != NULL)
            {
                hash_t *temp = arr[index].link;
                while(temp != NULL)
                {
                    if(temp->value == data)
                        return index;
                    temp = temp->link;
                }
                return DATA_NOT_FOUND;
            }
        }
    }
    return DATA_NOT_FOUND;
    
}