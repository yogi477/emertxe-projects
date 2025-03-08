#include "tree.h"

int find_height(Tree_t *root)
{
    if(root == NULL)
        return 0;
    int left = find_height(root->left);
    int right = find_height(root->right);
    if(left > right)
        return left + 1;
    else
        return right + 1;
}
