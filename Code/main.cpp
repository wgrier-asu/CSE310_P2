#include <iostream>
#include <cstring>
#include "defn.h"

using namespace std;

void printAppInfo(app_info *info);
void printAppInfo(app_info info);

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

        cout << app_categories[i]->category <<endl;
    }



    // Store data in BSTs
    int m; // # of applications
    cin >> m;
    cin.get();
    cout << "m = " << m << endl;
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

        //printAppInfo(newInfo);

        // Create BST
        bst *newBST = new bst[sizeof(bst)];
        newBST->record = *newInfo;


    }






    delete [] *app_categories;

    return 0;
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
    cout << info.price <<endl;
}
