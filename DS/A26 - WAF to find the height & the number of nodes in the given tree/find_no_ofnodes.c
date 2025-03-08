#include "tree.h"

int total_nodes(Tree_t *root)
{
     if(root == NULL)
        return 0;
    int left = total_nodes(root->left);
    int right = total_nodes(root->right);
    return left + right + 1;
}
