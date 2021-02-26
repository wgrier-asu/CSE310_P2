#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

#include "util.h"
#include "hash.h"

using namespace std;

int main() {
    // Create BST for Categories and Apps
    //      Forms an array of n categories with corresponding BSTs
    int n;     // number of categories
    cin >> n;  // get input
    cin.get(); // clear line
    categories *app_categories = new categories[n*sizeof(categories)]; // Create array of n categories

    // Initialize each category structure with name and BST (null)
    char *catName = new char[CAT_NAME_LEN];
    for(int i=0; i<n; i++){
        cin.getline(catName, CAT_NAME_LEN);
        strcpy(app_categories[i].category, catName);
        app_categories[i].root = NULL;
    }
    delete [] catName;
    catName = NULL;

    // Get # of Applications
    int tmpLength = 100;
    char *tmp = new char[tmpLength];
    int m; // # of applications
    cin.getline(tmp,tmpLength);
    sscanf(tmp, "%d", &m);

    // Create Hash Table
    int table_size = getHTSize(m);
    hash_table_entry **hash_table = new hash_table_entry*[table_size*sizeof(hash_table_entry)];
    for(int i=0; i<table_size; i++) hash_table[i] = NULL;


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

        // Create BST from app info
        bst *newBST = new bst[sizeof(bst)];
        newBST->record = *newInfo;
        newBST->right = NULL;
        newBST->left = NULL;

        // Insert the new BST into the correct category's binary search tree
        for(int i=0; i<n; i++){
            if(strcmp(newBST->record.category, app_categories[i].category) == 0){
                app_categories[i].root = insertBST(app_categories[i].root, newBST);
            }
        }

        // Insert the new BST into the hash table
        insertHash(hash_table, newBST);
    }





    // Read and Process Queries
    int qLength = 200;
    int q; // # of Queries
    cin.getline(tmp, tmpLength);
    sscanf(tmp, "%d", &q); // Get number of queries q
    memset(tmp, 0, tmpLength);

    char *queries[q]; // Array of size q to store q queries
    for(int i=0; i<q; i++){
        queries[i] = new char[qLength];
        cin.getline(queries[i], qLength); // Read each query into queries array
    }

    // Select and process each query
    int currQ = 0;
    int qType = -1;
    while(currQ < q){
        string query = queries[currQ];
        qType = getQType(query, qLength);
        // Note: qType corresponds to ordered list found in P2 Description PDF on Canvas

        // find app <app_name>
        if(qType == 1){
            // Get input name from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            char *inputName = new char[APP_NAME_LEN];
            strcpy(inputName, iCat.c_str());

            // Find BST in the Hash Table
            bst * search = searchHashTable(hash_table, inputName);

            // Output
            if(search == NULL) cout << "Application " << inputName << " not found." << endl;
            else{
                cout << "Found Application: " << inputName << endl;
                printAppInfo(search->record);
            }
        }
        // find max price apps <category>
        else if(qType == 2){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            const char *inputCategory = iCat.c_str();

            // Process Query with <inputCategory>
            bool DNE = true; // Does not exist = true
            for(int i=0; i<n; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    DNE = false;
                    find_max_price_query(app_categories[i]); // Print if category exists
                }
            }
            if(DNE){cout << "Category " << inputCategory << " not found." << endl;}
        }
        // print-apps <category>
        else if(qType == 3){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            const char *inputCategory = iCat.c_str();

            // Process Query with <inputCategory>
            bool DNE = true; // Does not exist = true
            for(int i=0; i<n; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    DNE = false;
                    print_apps_query(app_categories[i]);
                }
            }
            if(DNE){cout << "Category " << inputCategory << " not found." << endl;}
        }
        // find price free <category>
        else if(qType == 4){

        }
        // range <category> price <low> <high>
        else if(qType == 5){

        }
        // range <category> name <low> <high>
        else if(qType == 6){

        }
        // delete <category> <app_name>
        else if(qType == 7){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            char *inputCategory = new char[CAT_NAME_LEN];
            strcpy(inputCategory, iCat.c_str());

            // Get input app_name from the query
            int startOfName = query.find('\"',endOfCat+1) + 1;
            int endOfName = query.find('\"',startOfName);
            int nameLength = endOfName - startOfName;
            string iName = query.substr(startOfName, nameLength);
            char *inputName = new char[APP_NAME_LEN];
            strcpy(inputName, iName.c_str());


            // Check existence of category
            bool DNE = true; // Does not exist = true
            int catNum;
            for(int i=0; i<n; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    DNE = false;
                    catNum = i;
                }
            }
            // Category doesn't exist; quit query processing
            if(DNE){cout << "Application " << inputName << " not found in category " << inputCategory << "; unable to delete." << endl;}
            // Category exists; proceed with delete function
            else{
                // Deleted entry from hash table
                bool deleted = deleteEntry(hash_table, inputName, inputCategory);
                // Delete bst object from category BST
                app_categories[catNum].root = deleteNode(inputName, app_categories[catNum].root);

                // Successful Deletion
                if(deleted){
                    cout << "Application " << inputName << " from Category " << inputCategory << " successfully deleted." << endl;
                }
                // Failed Deletion
                else{
                    cout << "Application " << inputName << " not found in category " << inputCategory << "; unable to delete." << endl;
                }
            }
        }
        // Query Not Recognized
        else{
            cout << "--invalid query #" << currQ+1 << "--" << endl;
        }

        // Move to next query
        currQ++;
    }


    // Report Setting Output
    // Get "no report" or "report" from stdin
    cin.getline(tmp, tmpLength);
    string temp = tmp;
    delete [] tmp;
    int reportVal = temp.find("no report");
    bool report = true;
    if(reportVal > -1 && reportVal < tmpLength) report = false;

    if(report){
        // BST Statistics:
        cout << "BST Statistics" << endl;
        for (int i=0; i<n; i++){
            cout << "\t" << app_categories[i].category << endl;

            int totalCount = count(app_categories[i].root);
            cout << "\t\tTotal Nodes: " << totalCount << endl;

            int height = heightTree(app_categories[i].root);
            cout << "\t\tHeight: " << height << endl;

            if(totalCount == 0){
                cout << "\t\tNo Nodes Exist." << endl;
            }
            else if(height == 0){
                cout << "\t\tNo Subtrees Exist." << endl;
            }
            else{
                int heightL = heightTree(app_categories[i].root->left);
                cout << "\t\tHeight of Left Subtree: " << heightL << endl;

                int heightR = heightTree(app_categories[i].root->right);
                cout << "\t\tHeight of Right Subtree: " << heightR << endl;
            }
        }

        // Hash Table Statistics:

        // find app <app_name> - hash v. BST running time comparison

    }





    // Free Memory and Exit

    for(int i=0; i<n; i++){
        if(app_categories[i].root != NULL) app_categories[i].root = deleteTree(app_categories[i].root);
    }
    delete [] app_categories;


    return 0;
}