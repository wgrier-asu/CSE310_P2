#include <cmath>
#include <cstring>
#include "defn.h"


int left(int p){
    return 2*p;
}
int right(int p){
    return 2*p + 1;
}
int parent(int p){
    return floor(p/2);
}

/* insertBST
 * Description: inserts a new bst object into an existing BST
 * Input: root of existing BST, new bst object
 * */
bst * insertBST(bst *root, app_info *info){
    // Case 1: no BST has been established
    if(root == NULL) {
        root = new bst[sizeof(bst)];
        root->record = *info;
        root->right = NULL;
        root->left = NULL;
        return root;
    }
    // Case 2: new object is greater than root, insert into right child
    if(strcasecmp(info->app_name,root->record.app_name) > 0){
        root->right = insertBST(root->right, info);
    }
    // Case 3: new object is lesser than root, insert into left child
    else{
        root->left = insertBST(root->left, info);
    }
    return root;
}

/* Count
 * Returns the number of elements in the binary search tree
 * Input: bst *root */
int count(bst *root){
    // Base Case
    if(root == NULL) return 0;
    else{
        int count_left = 0;
        if(root->left != NULL) count_left = count(root->left);

        int count_right = 0;
        if(root->right != NULL) count_right = count(root->right);

        int sum = 1 + count_left + count_right;
        return sum;
    }
}

/* deleteTree
 * Description: deallocates memory of BST in post-order */
void deleteTree(bst *root){
    // Delete children recursively
    if(root->left != NULL) {
        deleteTree(root->left);
    }
    if(root->right != NULL) {
        deleteTree(root->right);
    }
    // Delete Root
    delete root;
}


