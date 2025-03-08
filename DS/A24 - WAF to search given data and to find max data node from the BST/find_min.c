#include "tree.h"

int findmin(Tree_t * root)
{
    if(root == NULL)
        return FAILURE;
    while(root->left)
    {
        root = root->left;
    }
    return root->data;
}
