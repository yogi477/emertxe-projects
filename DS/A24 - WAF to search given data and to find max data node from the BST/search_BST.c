#include "tree.h"

/* Iteratively */
int search_BST(Tree_t * root, int data)
{

    if(root == NULL)
    {
        return FAILURE;
    }
    Tree_t *temp = root;
    while(temp != NULL)
    {
      if(temp->data == data)
        return SUCCESS;
      if(temp->data > data)
         temp = temp->left;
      else if(temp->data < data)
        temp = temp->right;
       
    }
    return NOELEMENT;
}