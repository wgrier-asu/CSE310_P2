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
bst * insertBST(bst *root, bst *obj){
    // Case 1: no BST has been established
    if(root == NULL) {
        root = obj;
        return root;
    }
    // Case 2: new object is greater than root, insert into right child
    if(strcasecmp(obj->record.app_name,root->record.app_name) > 0){
        root->right = insertBST(root->right, obj);
    }
    // Case 3: new object is lesser than root, insert into left child
    else{
        root->left = insertBST(root->left, obj);
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

void deleteNode(bst *node){
    // do something
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

/* heightTree
 * Description: returns the height of the tree's longest branch */
int heightTree(bst *root){
    if(root == NULL) return 0;
    else{
        int heightLeft  = 1 + heightTree(root->left);
        int heightRight = 1 + heightTree(root->right);

        if(heightLeft > heightRight) return heightRight;
        else return heightLeft;
    }
}


