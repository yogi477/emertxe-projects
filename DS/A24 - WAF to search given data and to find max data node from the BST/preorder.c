#include "tree.h"

/* Function to print the tree in pre order */
int preorder(Tree_t *root)
{
    if(root != NULL)
   {
       printf("%d ",root->data);
       preorder(root->left);
       preorder(root->right);
   }
}