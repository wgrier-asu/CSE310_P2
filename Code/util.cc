#include <iostream>
#include <cstdio>
#include "bst.h"
#include "heap.h"
using namespace std;



/* print_app_names
 * Description: helper function to print_apps_query; Prints names of BST nodes by in-order traversal;
 *      In-order traversal yields alphabetical printing order. */
void print_app_names(bst *root){
    // Print left child's subtree
    if(root->left != NULL) print_app_names(root->left);
    // Print root app's name
    cout << "\t" << root->record.app_name << endl;
    // Print right child's subtree
    if(root->right != NULL) print_app_names(root->right);
}
/* Query: Print_Apps category <category_name>
 * Description: Recursive function; prints all apps within a given category by in-order traversal
 * Input: root of a category's BST
 * */
void print_apps_query(categories *cat){
    // Case 1: no apps in this category
    if(cat->root == NULL){
        cout << "Category <" << cat->category << "> no apps found." << endl;
    }
        // Case 2: print all apps
    else{
        cout << "Category: <" << cat->category << ">" << endl;
        print_app_names(cat->root);
    }
}


/* allocatePriceHeap
 * Description: uses in-order traversal of a BST to copy price values into a heap
 * */
int allocatePriceHeap(float *heap, int size, int pos, bst *root){
    // Left Sub-tree
    if(root->left != NULL){
        pos = allocatePriceHeap(heap, size, pos, root->left);
    }
    // Root node
    heap[pos] = root->record.price;
    pos++;
    // Right Sub-tree
    if(root->right != NULL){
        pos = allocatePriceHeap(heap, size, pos, root->right);
    }
    return pos; // return recursively to ensure heap position is continuously incremented
}
/* printIfPrice
 * Description: prints the app name if its price matches the priceKey */
void printIfPrice(bst *root, float priceKey){
    // Left Sub-tree
    if(root->left != NULL){
        printIfPrice(root->left, priceKey);
    }
    // Print Node if price matches priceKey
    if(root->record.price == priceKey) cout << "\t" << root->record.app_name <<endl;
    // Right Sub-tree
    if(root->right != NULL){
        printIfPrice(root->right, priceKey);
    }
}

/* Query: find max price <category>
 * Input: category to search
 * Description: finds and prints the app with the maximum price in the selected category
 * */
void find_max_price_query(categories *cat){
    // Case 1: no BST has been established
    if(cat->root == NULL) cout << "Category " << cat->category << " no apps found." << endl;
        // Case 2: Find the max and print
    else{
        // Get number of apps in the category
        int c = count(cat->root);

        // Allocate heap of size c and initialize with price data
        float *heap = new float[c];
        allocatePriceHeap(heap, c, 0, cat->root);

        // MaxHeapify the heap
        buildMaxHeap(heap, c);

        // Get maximum price in the category
        float maxPrice = Max(heap);
        // Truncate price to 2 decimal places only (currency format)
        char temp[10];
        sscanf(temp, "%.2f", maxPrice);
        sscanf(temp, "%f", &maxPrice);

        // Deallocate heap memory
        delete []heap;

        // Search and print all apps with the maximum price
        cout << "Category: " << cat->category << endl;
        printIfPrice(cat->root, maxPrice);
    }
}




/* getQType
 * Examines a query input and returns an integer corresponding to requested operation
 * Input: string query, int qLength (length of query)
 * Output: integer */
int getQType(string query, int qLength){
    // qType = index found in ordered list in P2 description document
    int qType = -1;
    int loc = -1;

    // 1. find app
    loc = query.find("find app");
    if(loc > -1 && loc < qLength) qType = 1;

    // 2. find max price apps
    loc = query.find("find max price apps");
    if(loc > -1 && loc < qLength) qType = 2;

    // 3. print-apps category
    loc = query.find("print-apps category");
    if(loc > -1 && loc < qLength) qType = 3;

    // 4. find price free
    loc = query.find("find price free");
    if(loc > -1 && loc < qLength) qType = 4;

    // 5-6. range
    loc = query.find("range");
    if(loc > -1 && loc < qLength) {
        loc = query.find("price");
        if(loc > -1 && loc < qLength) qType = 5; // range price
        else qType = 6;                          // range app
    }

    // 7. delete
    loc = query.find("delete");
    if(loc > -1 && loc < qLength) qType = 7;

    return qType;
}


/* printAppInfo
 * Description: prints all data within an app_info object */
void printAppInfo(app_info *info){
    cout << info->category << endl;
    cout << info->app_name <<endl;
    cout << info->version <<endl;
    cout << info->size <<endl;
    cout << info->units <<endl;
    cout << info->price <<endl;
}
/* printAppInfo
 * Description: prints all data within an app_info object */
void printAppInfo(app_info info){
    cout << info.category <<endl;
    cout << info.app_name <<endl;
    cout << info.version   << endl;
    cout << info.size <<endl;
    cout << info.units   <<endl;
    cout << info.price <<endl;
}