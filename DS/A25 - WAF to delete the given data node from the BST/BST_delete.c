#include "tree.h"

extern int status;
/* Function to delete the node  */
Tree_t * delete_BST(Tree_t * root, int data)
{
    //base
    if(root == NULL)
        return NULL;
    
    //searching node
    if(data < root->data)
    {
        root->left = delete_BST(root->left,data);
    }
    else if(data > root->data)
    {
        root->right = delete_BST(root->right,data);
    }
     
    //deletion if data found
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            status = 1;
            return NULL;
        
        }
        else if(root->left == NULL)
        {
            Tree_t *temp = root->right;
            free(root);
            status = 1;
            return temp;
        }
        else if(root->right == NULL)
        {
            Tree_t *temp = root->left;
            free(root);
            status = 1;
            return temp;
        }
        else
        {
            root->data =  findmin(root->left);
            root->left = delete_BST(root->left,root->data);
        }
        
    }
    return root;
}