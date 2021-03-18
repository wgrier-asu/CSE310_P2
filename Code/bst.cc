#include <cmath>
#include <iostream>
#include <cstring>
#include "Headers/defn.h"
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

bst *minParent(bst *x){
    // Base Case: x is the min or x.left is the min
    if(x->left == NULL || x->left->left == NULL) return x;
    // Recursive: find minParent of left (smaller) child's subtree
    else return minParent(x->left);
}

// Inspired by: https://stackoverflow.com/questions/3796003/find-the-successor-without-using-parent-pointer
bst * successor(bst * x, bst *catRoot){
    if(x->right != NULL) return min(x->right);
    else{ // Find smallest element greater than x
        // No parent functionality, must traverse down from top of tree
        bst *succ = NULL;
        bst *curr = catRoot;
        bool searching = true;

        // Set while condition
        if(curr == NULL) searching = false;
        if(curr == x) searching = false;

        // Stop traversing when at a leaf or the original element is found
        while(searching) {
            // Case 1: curr is greater than x, move left to find possible smaller element
            if (strcmp(curr->record.app_name, x->record.app_name) > 0) {
                // Set the possible successor
                succ = curr;
                // Move curr to left subtree
                curr = curr->left;
            }
                // Case 2: curr is less than x, not a possible successor, shift right
            else {
                // Move curr to right subtree
                curr = curr->right;
            }

            // Set while condition
            if(curr == NULL) searching = false;
            if(curr == x) searching = false;
        }

        return succ;
    }
}

bst * predecessor(bst *root){
    if(root->left != NULL) return max(root->left);
    else{
        return root; // WRONG: (see OneNote)
    }
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
            // Case 3.3.1: Right child is the successor
            if(root->right->left == NULL){
                bst *succ = root->right;
                // Preserve Tree
                root->record = succ->record;
                root->right = succ->right; // link to right subtree
                // Delete successor
                delete [] succ;
            }
            // Case 3.3.2: Find the successor in the right subtree
            else{
                // Find successor's parent (the parent of the minimum of the right subtree)
                //      Using successor function is unnecessary because only finding successor if the right subtree exists
                bst *succParent = minParent(root->right);
                bst *succ = succParent->left;
                // Preserve successor's right subtree
                succParent->right = succ->right;
                // Copy successor data to root
                root->record = succ->record;
                // Delete successor leaf node
                delete [] succ;
            }



            /*
            bst *pred = predecessor(root);
            // Copy values to root
            root->record = pred->record;
            // Delete predecessor by recursion, finds leaf node and deletes
            root->left = deleteNode(pred->record.app_name, root->left);
            // Return new root (same root, but different values; structure unchanged)
             */
        }
    }
    return root;
}
/*
void deleteNode2(bst *x, bst * treeRoot){
    // Find x, the node to delete
    //bst *x = searchNode(key, treeRoot);
    // No children, delete x
    if(x->left == NULL && x->right == NULL){
        delete [] x;
        x = NULL;
    }
    // No left child, set x to right tree root
    else if(x->left == NULL) {
        x = x->right;
    }
    // No right child, set x to left tree root
    else if(x->right == NULL){
        x = x->left;
    }
    // Both children exist
    else{
        // Right child's left child is NULL, so right child is the successor (smallest greater than x)
        if(x->right->left == NULL) x = x->right;
        // Right child is no the successor, find successor
        else {
            bst *succ = successor(x, treeRoot);
            // Transplant data
            x->record = succ->record;
            // Fix right subtree
            deleteNode2(succ, treeRoot); // Does this work?
        }
    }
}
*/


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


