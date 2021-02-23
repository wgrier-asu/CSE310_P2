#include <iostream>
#include <cstring>
#include "defn.h"

using namespace std;

void printAppInfo(app_info *info);
void printAppInfo(app_info info);
void print_apps(bst *root);
void print_apps_query(categories *cat);


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
    int m; // # of applications
    cin >> m;
    cin.get();
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
        cin >> newInfo->size;
        cin.get();
        // Units char[]
        cin.getline(newInfo->units, UNIT_SIZE);
        // Price float
        cin >> newInfo->price;
        cin.get();


        // Insert the new BST info into the correct category binary search tree
        for(int i=0; i<n; i++){
            if(strcmp(newInfo->category, app_categories[i]->category) == 0){
                app_categories[i]->root = insertBST(app_categories[i]->root, newInfo);
            }
        }


    }

    // Print_Apps Query
    // input: char[]
    char *inputCategory = "Medical";
    // Check that input category exists
    bool DNE = true; // Does not exist = true
    for(int i=0; i<n; i++){
        if(strcmp(app_categories[i]->category,inputCategory)==0){
            DNE = false;
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
