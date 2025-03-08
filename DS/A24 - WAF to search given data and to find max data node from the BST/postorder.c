#include "tree.h"

/* Function to print the tree in post order */
int postorder(Tree_t *root)
{
     if(root != NULL)
   {
       postorder(root->left);
       postorder(root->right);
       printf("%d ",root->data);
   }
}