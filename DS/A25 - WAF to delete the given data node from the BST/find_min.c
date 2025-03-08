#include "tree.h"

int findmin(Tree_t * root)
{
    if(root == NULL)
        return 1;
    while(root->right)
    {
        root = root->right;
    }
    return root->data;
}
