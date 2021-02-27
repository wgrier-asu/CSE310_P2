#include <cmath>
#include <iostream>
#include <cstring>
#include "defn.h"
using namespace std;

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
bst * successor(bst * root){
    if(root->right != NULL) return min(root->right);
    else{
        return root; // WRONG: see implementation (see OneNote)
    }
    return min(root->right);
}
bst * predecessor(bst *root){
    if(root->left != NULL) return max(root->left);
    else{
        return root; // WRONG: (see OneNote)
    }
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
        root->right = deleteTree(root->right);
        root->left = deleteTree(root->left);
        delete [] root;
        root = NULL;
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
        // Case 3.1: Key is at leaf node or has right child only
        if(root->left == NULL){
            bst * newRoot = root->right; // right could be NULL or root of subtree
            delete [] root;
            root = NULL;
            return newRoot;
        }
        // Case 3.2: Key has left child only, return left child as new root
        else if(root->right == NULL){
            bst *newRoot = root->left;
            delete [] root;
            root = NULL;
            return newRoot;
        }
        // Case 3.3: Key has both children
        //          Set new root to predecessor value; delete predecessor leaf node
        else{
            // Find predecessor (leaf node)
            bst * pred = predecessor(root);
            // Copy values to root
            root->record = pred->record;
            // Delete predecessor by recursion, finds leaf node and deletes
            root->left = deleteNode(pred->record.app_name, root->left);
            // Return new root (same root, but different values; structure unchanged)
        }
    }
    return root;
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

/* heightTree
 * Description: returns the height of the tree's longest branch */
int heightTree(bst *root){
    if(root == NULL) return 0;
    else{
        int heightLeft  = 1 + heightTree(root->left);
        int heightRight = 1 + heightTree(root->right);

        if(heightLeft > heightRight) return heightLeft;
        else return heightRight;
    }
}


