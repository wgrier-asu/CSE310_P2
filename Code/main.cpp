#include <iostream>
#include <cstring>
#include "defn.h"
#include <math.h>

using namespace std;

void printAppInfo(app_info *info);
void printAppInfo(app_info info);
void print_apps(bst *root);
void print_apps_query(categories *cat);

int count(bst *root);
int allocatePriceHeap(float heap[], int size, int pos, bst *root);
void printIfPrice(bst *root, float priceKey);
void buildMaxHeap(float heap[], int size);
void maxHeapify(float heap[], int pos, int size);
float Max(float heap[]);
int right(int p);
int left(int p);
int parent(int p);



/* Returns the object(s) with the maximum price*/
bst * find_max_price_query(categories *cat){
    // Case 1: no BST has been established
    if(cat->root == nullptr) cout << "Category <" << cat->category << "> no apps found." << endl;
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

        // Search and print all apps with the maximum price
        printIfPrice(cat->root, maxPrice);
    }
}
float Max(float heap[]){
    return heap[0];
}
int count(bst *root){
    // Base Case
    if(root == nullptr) return 0;
    else{
        int count_left = count(root->left);
        int count_right = count(root->right);
        int sum = 1 + count_left + count_right;
        return sum;
    }
}
int allocatePriceHeap(float heap[], int size, int pos, bst *root){
    // Left Sub-tree
    if(root->left != nullptr){
        pos = allocatePriceHeap(heap, size, pos, root->left);
    }
    // Root node
    heap[pos] = root->record.price;
    pos++;
    // Right Sub-tree
    if(root->right != nullptr){
        pos = allocatePriceHeap(heap, size, pos, root->right);
    }
    return pos; // ensure position value is continuous throughout in-order traversal
}
void printIfPrice(bst *root, float priceKey){
    // Left Sub-tree
    if(root->left != nullptr){
        printIfPrice(root->left, priceKey);
    }
    // Print Node if price matches priceKey
    if(root->record.price == priceKey) cout << root->record.app_name <<endl;
    // Right Sub-tree
    if(root->right != nullptr){
        printIfPrice(root->right, priceKey);
    }
}
void buildMaxHeap(float heap[], int size){
    int firstParent = floor(size/2);
    for(int i=firstParent; i>0; i--){
        maxHeapify(heap, i, size);
    }
}
void maxHeapify(float heap[], int pos, int size){
    int l = left(pos)-1;
    int r = right(pos)-1;
    pos--;
    // Note: subtraction is to adjust index from [1..n] to [0..n-1]

    // Find the largest value's position
    int largest = pos;
    if(l <= size && heap[l] > heap[largest]){
        largest = l;
    }
    if(r <= size && heap[r] > heap[largest]){
        largest = r;
    }

    // Swap if current object is not the largest
    if(largest != pos){
        float temp = heap[pos];
        heap[pos] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, largest+1, size);
    }
}
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
    if(root == nullptr) {
        root = new bst[sizeof(bst)];
        root->record = *info;
        root->right = nullptr;
        root->left = nullptr;
    }
    // Case 2: new object is greater than root, insert into right child
    else if(strcmp(info->app_name,root->record.app_name) > 0){
        root->right = insertBST(root->right, info);
    }
    // Case 3: new object is lesser than root, insert into left child
    else{
        root->left = insertBST(root->left, info);
    }
    return root;
}








int main() {
    // 1.1.1 BST for Categories
    //      Forms an array of n categories with corresponding BSTs
    int n;     // number of categories
    cin >> n;  // get input
    cin.get(); // clear line
    categories *app_categories [n]; // Create array of n categories

    // Initialize each category structure with name and BST (null)
    char *catName = new char[CAT_NAME_LEN];
    for(int i=0; i<n; i++){
        app_categories[i] = new categories[sizeof(categories)];
        cin.getline(catName, CAT_NAME_LEN);
        strcpy(app_categories[i]->category, catName);
        app_categories[i]->root = nullptr;
    }

    // Store data in BSTs
    int tmpLength = 100;
    char *tmp = new char[tmpLength];

    int m; // # of applications
    cin.getline(tmp,tmpLength);
    sscanf(tmp, "%d", &m);

    // Initialize the BSTs
    for(int i=0; i<m; i++){
        // Create and fill app_info structure
        app_info *newInfo = new app_info[sizeof(app_info)];

        // Category char[]
        cin.getline(newInfo->category, CAT_NAME_LEN);
        // App_Name char[]
        cin.getline(newInfo->app_name, APP_NAME_LEN);
        // Version char[]
        cin.getline(newInfo->version, VERSION_LEN);
        // Size float
        cin.getline(tmp, 100);
        sscanf(tmp, "%f", &newInfo->size);
        memset(tmp, 0, 100);
        // Units char[]
        cin.getline(newInfo->units, UNIT_SIZE);
        // Price float
        cin.getline(tmp, 100);
        sscanf(tmp, "%f", &newInfo->price);
        memset(tmp, 0, 100);



        // Insert the new BST info into the correct category binary search tree
        for(int i=0; i<n; i++){
            if(strcmp(newInfo->category, app_categories[i]->category) == 0){
                app_categories[i]->root = insertBST(app_categories[i]->root, newInfo);
            }
        }

    }





    // TEST QUERY AREA
    // input: char[]
    char *inputCategory = "Food & Drink";
    // Check that input category exists
    bool DNE = true; // Does not exist = true
    for(int i=0; i<n; i++){
        if(strcmp(app_categories[i]->category,inputCategory)==0){
            DNE = false;
            find_max_price_query(app_categories[i]); // Print if category exists
            print_apps_query(app_categories[i]); // Print if category exists
        }
    }
    if(DNE){cout << "Category <" << inputCategory << "> not found." << endl;}







    delete [] *app_categories;

    return 0;
}




/* Query: Print_Apps category <category_name>
 * Description: Recursive function; prints all apps within a given category by in-order traversal
 * Input: root of a category's BST
 * */
void print_apps_query(categories *cat){
    // Case 1: no apps in this category
    if(cat->root == nullptr){
        cout << "Category <" << cat->category << "> no apps found." << endl;
    }
    // Case 2: print all apps
    else{
        cout << "Category: <" << cat->category << ">" << endl;
        print_apps(cat->root);
    }
}
void print_apps(bst *root){
    // Print left child's subtree
    if(root->left != nullptr) print_apps(root->left);
    // Print root app's name
    cout << "\t" << root->record.app_name << endl;
    // Print right child's subtree
    if(root->right != nullptr) print_apps(root->right);
}






void printAppInfo(app_info *info){
    cout << info->category << endl;
    cout << info->app_name <<endl;
    cout << info->version <<endl;
    cout << info->size <<endl;
    cout << info->units <<endl;
    cout << info->price <<endl;
}
void printAppInfo(app_info info){
    cout << info.category <<endl;
    cout << info.app_name <<endl;
    cout << info.version   << endl;
    cout << info.size <<endl;
    cout << info.units   <<endl;
    cout << info.price <<endl;
}
