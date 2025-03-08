#include "tree.h"

int findmax(Tree_t * root)
{
    if(root == NULL)
        return FAILURE;
    while(root->right)
    {
        root = root->right;
    }
    return root->data;
}
