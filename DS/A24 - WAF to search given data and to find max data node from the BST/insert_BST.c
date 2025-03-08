#include "tree.h"

/* Function to insert the data's in BST */
int insert_into_BST(Tree_t **root, int data)
{
    Tree_t *newn = malloc(sizeof(Tree_t));
    if(newn == NULL)
        return FAILURE;
    newn->left = NULL;
    newn->data = data;
    newn->right = NULL;
    int flag = 0;
    if(*root == NULL)
    {
        *root = newn;
        return SUCCESS;
    }
    Tree_t *temp = *root;
    Tree_t *parent = NULL;
    while(temp != NULL)
    {
      parent = temp;
      if(temp->data == data)
        return DUPLICATE;
      if(temp->data > data)
         temp = temp->left;
      else if(temp->data < data)
        temp = temp->right;
       
    }
    if(parent->data < data)
        parent->right = newn;
    else
        parent->left = newn;
        
    return SUCCESS;
    
}