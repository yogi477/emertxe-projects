#include"hash.h"

int insert_HT(hash_t *arr, int element, int size)
{
    int index = element % size;
    if(arr[index].value == -1)
    {
        arr[index].value = element;
        return SUCCESS;
    }
    else
    {
        hash_t *new1 = malloc(sizeof(hash_t));
        new1->index = index;
        new1->value = element;
        new1->link = NULL;
        if(arr[index].link == NULL)
        {
            arr[index].link = new1;
            return SUCCESS;
        }
        else
        {
            hash_t *temp = arr[index].link;
            while(temp->link != NULL)
            {
                temp = temp->link;
            }
            temp->link = new1;
            return SUCCESS;
        }
    }
}