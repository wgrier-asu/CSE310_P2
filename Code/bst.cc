#include <cmath>
#include <iostream>
#include <cstring>
#include "Headers/defn.h"
using namespace std;


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
    // Lexicographic (case-sensitive) - use strcmp
    // Alphabetical (case-insensitive) - use strcasecmp -- also change Delete()
    if(strcmp(obj->record.app_name,root->record.app_name) > 0){
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


bst * min(bst *root){
    // Base: no more elements less than root
    if(root->left==NULL) return root;
    // Recursive: find left (smaller) child
    else return min(root->left);
}
bst * max(bst *root){
    // Base: no more elements greater than root
    if(root->right==NULL) return root;
    // Recursive: find right (larger) child
    else return max(root->right);
}

bst *minParent(bst *x){
    // Base Case: x is the min or x.left is the min
    if(x->left == NULL || x->left->left == NULL) return x;
    // Recursive: find minParent of left (smaller) child's subtree
    else return minParent(x->left);
}


/* searchNode
 * Description: searches for and returns a node based on key app_name
 * */
bst * searchNode(char *key, bst *root){
    // Case 0: Tree doesn't exist
    if(root == NULL) return NULL;
    else if(strcmp(key, root->record.app_name) == 0) return root;
    else if(strcmp(key, root->record.app_name) < 0) return searchNode(key, root->left);
    else return searchNode(key, root->right);
}


bst * delThisNode(bst *root) {
    // Case 0: NULL
    if(root == NULL) return root;
    // Case 1-2: Only Left Child Exists OR No Children
    else if(root->right == NULL){
        bst *newRoot = root->left;
        delete [] root;
        root = NULL;
        return newRoot;
    }
    // Case 3: Only Right Child Exists
    else if(root->left == NULL){
        bst *newRoot = root->right;
        delete [] root;
        root = NULL;
        return newRoot;
    }
    // Case 4: Return successor
    else{
        bst *successorParent = minParent(root->right);
        // Swap data
        root->record = successorParent->left->record; // Root = Successor (data, maintain root's children)
        delete [] successorParent->left;
        successorParent->left = NULL;
        return root;
    }
}

/* deleteNode
 * Description: deletes the object corresponding to the input key
 * Return: root of BST
 * */
bst * deleteNode(char *key, bst * root){
    // Case 0: Tree doesn't exist
    if(root == NULL) return NULL; // returns NULL tree
    // Case 1: Key is right of (greater than) root
    else if(strcmp(key,root->record.app_name) > 0) root->right = deleteNode(key, root->right);
    // Case 2: Key is left of (lesser than) root
    else if(strcmp(key, root->record.app_name) < 0) root->left = deleteNode(key, root->left);
    // Case 3: Key is at root, delete
    else{
        root = delThisNode(root);
        if(root) cout << "new root: " << root->record.app_name << endl;
        else cout << "deleted at a leaf" << endl;
    }
    return root;
}



/* deleteTree
 * Description: Deletes an entire BST
 * Return: NULL root node
 * */
bst * deleteTree(bst *root){
    // Case 0: No tree
    if(root == NULL) return NULL;
    // Case 1: Delete Children, Delete Root, Return Null
    else{
        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);
        delete [] root;
        root = NULL;
        return root;
    }
}



/* heightTree
 * Description: returns the height of the tree's longest branch */
int heightTree(bst *root){
    if(root == NULL) return 0;
    else{
        int heightLeft = 0;
        int heightRight = 0;
        if(root->left != NULL) heightLeft = 1 + heightTree(root->left);
        if(root->right != NULL) heightRight = 1 + heightTree(root->right);


        if(heightLeft > heightRight) return heightLeft;
        else return heightRight;
    }
}


