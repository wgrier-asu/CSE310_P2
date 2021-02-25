#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

#include "util.h"

using namespace std;

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
        app_categories[i]->root = NULL;
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

        if(qType == 1){

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
                if(strcmp(app_categories[i]->category,inputCategory)==0){
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
                if(strcmp(app_categories[i]->category,inputCategory)==0){
                    DNE = false;
                    print_apps_query(app_categories[i]);
                }
            }
            if(DNE){cout << "Category " << inputCategory << " not found." << endl;}
        }
        else if(qType == 4){

        }
        else if(qType == 5){

        }
        else if(qType == 6){

        }
        else if(qType == 7){

        }
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
    int reportVal = temp.find("no");
    bool report = true;
    if(reportVal > -1 && reportVal < tmpLength) report = false;

    if(report){
        // BST Statistics:
        cout << "BST Statistics" << endl;
        for (int i=0; i<n; i++){
            cout << "\t" << app_categories[i]->category << endl;

            int totalCount = count(app_categories[i]->root);
            cout << "\t\tTotal Nodes: " << totalCount << endl;

            int height = log2(totalCount);
            if(totalCount == 0) height = 0;
            cout << "\t\tHeight: " << height << endl;

            if(totalCount == 0){
                cout << "\t\tNo Nodes Exist." << endl;
            }
            else if(height == 0){
                cout << "\t\tNo Subtrees Exist." << endl;
            }
            else{
                int countL = count(app_categories[i]->root->left);
                int heightL = log2(countL);
                if(countL == 0) heightL = 0;
                cout << "\t\tHeight of Left Subtree: " << heightL << endl;

                int countR = count(app_categories[i]->root->right);
                int heightR = log2(countR);
                if(countR == 0) heightR = 0;
                cout << "\t\tHeight of Right Subtree: " << heightR << endl;
            }
        }

        // Hash Table Statistics:

        // find app <app_name> - hash v. BST running time comparison

    }






    // Free Memory and Exit

    for(int i=0; i<n; i++){
        if(app_categories[i]->root != NULL) deleteTree(app_categories[i]->root);
    }
    delete [] *app_categories;

    return 0;
}
