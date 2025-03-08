#include "tree.h"

/* Function to print the data in in order printing */
int inorder(Tree_t *root)
{
   if(root != NULL)
   {
       inorder(root->left);
       printf("%d ",root->data);
       inorder(root->right);
   }
}