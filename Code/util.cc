#include <iostream>
#include <cstdio>
#include <cstring>
#include "Headers/bst.h"
#include "Headers/heap.h"
using namespace std;


/* print_app_names
 * Description: helper function to print_apps_query; Prints names of BST nodes by in-order traversal;
 *      In-order traversal yields alphabetical printing order. */
void print_app_names_in_order(bst *root){
    // Print left child's subtree
    if(root->left != NULL) print_app_names_in_order(root->left);
    // Print root app's name
    cout << "\t" << root->record.app_name << endl;
    // Print right child's subtree
    if(root->right != NULL) print_app_names_in_order(root->right);
}

/* Query: Print_Apps category <category_name>
 * Description: Recursive function; prints all apps within a given category by in-order traversal
 * Input: root of a category's BST
 * */
void print_apps_query(bst *root){
    // Case 1: no apps in this category
    if(root == NULL) return;
    // Case 2: print all apps
    else print_app_names_in_order(root); // in-order traversal
}

/* allocatePriceHeap
 * Description: uses in-order traversal of a BST to copy price values into a heap (array)
 * */
int allocatePriceHeap(float *heap, int size, int pos, bst *root){
    // Left Sub-tree
    if(root->left != NULL){
        pos = allocatePriceHeap(heap, size, pos, root->left);
    }

    // Root node
    if(root->record.price < 0.01) heap[pos] = 0;
    else heap[pos] = root->record.price;
    pos++;

    // Right Sub-tree
    if(root->right != NULL){
        pos = allocatePriceHeap(heap, size, pos, root->right);
    }
    return pos; // return recursively to ensure heap position is continuously incremented
}

/* findPrice
 * Description: returns 1 if an object with a certain price exists in the BST
 * Pre-order Traversal */
bool findPrice(bst *root, float priceKey){
    bool exists = false;

    if(root->record.price == priceKey) return true;
    else{
        // Left Sub-Tree
        if(root->left != NULL) exists = findPrice(root->left, priceKey);

        if(exists) return exists; // Price found in left sub-tree, return true
        else{ // Check Right sub-tree
            // Right-Tree
            if(root->right != NULL) exists = findPrice(root->right, priceKey);
            else return false;
        }
    }

    return exists;
}

/* printIfPrice
 * Description: searches and prints the app name if its price matches the priceKey
 * In-order traversal */
void printIfPrice(bst *root, float priceKey){
    // Left Sub-tree
    if(root->left != NULL) printIfPrice(root->left, priceKey);
    // Print Node if price matches priceKey
    if(root->record.price == priceKey) cout << "\t" << root->record.app_name <<endl;
    // Right Sub-tree
    if(root->right != NULL) printIfPrice(root->right, priceKey);
}

/* Query: find max price <category>
 * Input: category to search
 * Description: finds and prints the app with the maximum price in the selected category
 * */
void find_max_price_query(bst * root){
    // Case 1: no BST has been established
    if(root == NULL) return;
    // Case 2: Find the max and print
    else{
        // Get number of apps in the category
        int c = count(root);

        // Allocate heap of size c and initialize with price data
        float *heap = new float[c];
        allocatePriceHeap(heap, c, 0, root);


        // MaxHeapify the heap
        buildMaxHeap(heap, c);


        // Get maximum price in the category
        float maxPrice = Max(heap);
        // Truncate price to 2 decimal places only (currency format)
        char temp[10] = "";
        sscanf(temp, "%.2f", maxPrice);
        sscanf(temp, "%f", &maxPrice);

        // Deallocate heap memory
        delete [] heap;

        // Search and print all apps with the maximum price
        printIfPrice(root, maxPrice);
    }
}
/* findInRange
 * Description: returns true if an object with a certain price exists in the BST
 * Pre-order Traversal */
bool findInRange(bst *root, float low, float high){
    bool exists = false;

    if(root->record.price >= low && root->record.price <= high) return true;
    else{
        // Left Sub-Tree
        if(root->left != NULL) exists = findInRange(root->left, low, high);

        if(exists) return exists; // Price found in left sub-tree, return true
        else{ // Check Right sub-tree
            // Right-Tree
            if(root->right != NULL) exists = findInRange(root->right, low, high);
            else return false;
        }
    }

    return exists;
}

/* Print_range_in_order; float keys
 * Print app_names in-order traversal between char keys low and high */
void print_range_in_order(bst *root, float low, float high){
    // Left Sub-tree
    if(root->left != NULL) print_range_in_order(root->left, low, high);
    // Root
    if(root->record.price >= low && root->record.price <= high) cout << "\t" << root->record.app_name << endl;

    // Right Sub-tree
    if(root->right != NULL) print_range_in_order(root->right, low, high);
}


/* Print_range_in_order; char keys
 * Print app_names in-order traversal between char keys low and high */
void print_range_in_order(bst *root, const char *low, const char *high){
    // Left Sub-tree
    if(root->left != NULL && strcmp(low, root->left->record.app_name) <= 0) print_range_in_order(root->left, low, high);
    // Root
    cout << "\t" << root->record.app_name << endl;
    // Right Sub-tree
    if(root->right != NULL && strcmp(high, root->right->record.app_name) >= 0) print_range_in_order(root->right, low, high);
}

/* print_in_range for char key
 * Description: manages under/overflow for searching and printing all with app_name in range (low,high)
 * */
bool print_in_range(bst *root, const char *low, const char *high){
    bool OutOfRange;
    // If root doesn't exist, or we've reached end of branch
    if(root==NULL) {
        OutOfRange = true;
    }
    // Find maximum root if current root is too high
    //      Returns true if entire tree is out of range
    else if(strcmp(high, root->record.app_name) < 0){
        OutOfRange = print_in_range(root->left, low, high);
    }
    // Find minimum root, if current root is too low
    //      Returns true if entire tree is out of range
    else if(strcmp(low, root->record.app_name) > 0){
        OutOfRange = print_in_range(root->right, low, high);
    }
    // Element is in range
    //      In-Order Traversal and Print
    else{
        OutOfRange = false;
        cout << "Applications in Range (" << low << "," << high << ") in Category: \"" << root->record.category <<"\""<< endl;
        print_range_in_order(root, low, high);
    }
    return OutOfRange;
}

/* getQType
 * Examines a query input and returns an integer corresponding to requested operation
 * Input: string query, int qLength (length of query)
 * Output: integer */
int getQType(string query, int qLength){
    // return int = index found in ordered list in P2 description document
    int loc;

    // 1. find app
    loc = query.find("find app");
    if(loc > -1 && loc < qLength) return 1;

    // 2. find max price apps
    loc = query.find("find max price apps");
    if(loc > -1 && loc < qLength) return 2;

    // 3. print-apps category
    loc = query.find("print-apps category");
    if(loc > -1 && loc < qLength) return 3;

    // 4. find price free
    loc = query.find("find price free");
    if(loc > -1 && loc < qLength) return 4;

    // 5-6. range
    loc = query.find("range");
    if(loc > -1 && loc < qLength) {
        loc = query.find("price");
        if(loc > -1 && loc < qLength) return 5; // range price
        else return 6;                          // range app
    }

    // 7. delete
    loc = query.find("delete");
    if(loc > -1 && loc < qLength) return 7;

    // 8. no report
    loc = query.find("report");
    if(loc > -1 && loc < qLength) {
        loc = query.find("no");
        if(loc > -1 && loc < qLength) return 8; // no report
        else return 9; // report
    }

    return -1; // invalid query = -1
}


/* printAppInfo
 * Description: prints all data within an app_info object */
void printAppInfo(app_info info){
    cout << "\tCategory: " << info.category <<endl;
    cout << "\tApplication Name: " << info.app_name <<endl;
    cout << "\tVersion: " << info.version   << endl;
    cout << "\tSize: " << info.size <<endl;
    cout << "\tUnits: " << info.units   <<endl;
    printf("\tPrice: $%.2f\n",info.price);
}

