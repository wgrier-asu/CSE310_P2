#include <iostream>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "Headers/util.h"

using namespace std;

int main() {
    // Create BST for Categories and Apps
    //      Forms an array of n categories with corresponding BSTs
    int numCategories;     // number of categories
    cin >> numCategories;  // get input
    cin.get(); // clear line
    categories *app_categories = new categories[numCategories*sizeof(categories)]; // Create array of n categories

    // Initialize each category structure with name and BST (null)
    char *catName = new char[CAT_NAME_LEN];
    for(int i=0; i<numCategories; i++){
        cin.getline(catName, CAT_NAME_LEN);
        strcpy(app_categories[i].category, catName);
        app_categories[i].root = NULL;
    }
    delete [] catName;
    catName = NULL;

    // Get # of Applications
    int tmpLength = 100;
    char *tmp = new char[tmpLength];
    int numApps; // # of applications
    cin.getline(tmp,tmpLength);
    sscanf(tmp, "%d", &numApps);
    delete [] tmp;
    tmp = NULL;

    // Create Hash Table
    int table_size = getHTSize(numApps);
    hash_table_entry **hash_table = new hash_table_entry*[table_size*sizeof(hash_table_entry)];
    for(int i=0; i<table_size; i++) hash_table[i] = NULL;


    // Initialize the BSTs
    for(int i=0; i<numApps; i++){
        // Create and fill app_info structure
        app_info *newInfo = new app_info[sizeof(app_info)];
        tmp = new char[tmpLength];

        // Category char[]
        cin.getline(newInfo->category, CAT_NAME_LEN);
        // App_Name char[]
        cin.getline(newInfo->app_name, APP_NAME_LEN);
        // Version char[]
        cin.getline(newInfo->version, VERSION_LEN);
        // Size float
        cin.getline(tmp, tmpLength);
        sscanf(tmp, "%f", &newInfo->size);
        memset(tmp, 0, tmpLength);
        // Units char[]
        cin.getline(newInfo->units, UNIT_SIZE);
        // Price float
        cin.getline(tmp, tmpLength);
        sscanf(tmp, "%f", &newInfo->price);
        memset(tmp, 0, tmpLength);

        // Create BST from app info

        bst *newBST = new bst[sizeof(bst)];
        newBST->record = *newInfo;
        newBST->right = NULL;
        newBST->left = NULL;

        // Insert the new BST into the correct category's binary search tree
        for(int i=0; i<numCategories; i++){
            if(strcmp(newBST->record.category, app_categories[i].category) == 0){
                app_categories[i].root = insertBST(app_categories[i].root, newBST);
            }
        }

        // Insert the new BST into the hash table
        insertHash(hash_table, newBST, table_size);

        delete [] tmp;
        delete [] newInfo;
    }


    // Read and Process Queries
    int qLength = 200;
    int q; // # of Queries
    tmp = new char[tmpLength];
    cin.getline(tmp, tmpLength);
    sscanf(tmp, "%d", &q); // Get number of queries q
    memset(tmp, 0, tmpLength);
    delete [] tmp;


    char *queries[q]; // Array of size q to store q queries
    for(int i=0; i<q; i++){
        queries[i] = new char[qLength];
        cin.getline(queries[i], qLength); // Read each query into queries array
    }


    // Select and process each query
    int currQ = 0;
    int qType = -1;
    bool reportCommand = false;
    while(currQ < q){
        string query = queries[currQ];
        qType = getQType(query, qLength);
        // Note: qType corresponds to ordered list found in P2 Description PDF on Canvas

        // Echo Query/Update
        cout << query << endl;

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
            bst * search = searchHashTable(hash_table, inputName, table_size);

            // Output
            if(search == NULL) cout << "Application \"" << inputName << "\" not found." << endl;
            else{
                cout << "Found Application: \"" << inputName <<"\""<< endl;
                printAppInfo(search->record);
            }

            delete [] inputName;
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
            int instruction = 0;
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    if(app_categories[i].root == NULL) instruction = 1;
                    else{ instruction = 2; catNum = i;}
                }
            }
            // Case 0: No Category Exists
            if(instruction == 0){cout << "Category \"" << inputCategory << "\" not found." << endl;}
            // Case 1: Category BST is Empty
            else if(instruction ==1){cout << "Category \"" << inputCategory << "\" no apps found." << endl;}
            // Case 2: Execute Query
            else{
                cout << "Category: \"" << inputCategory <<"\""<< endl;
                find_max_price_query(app_categories[catNum].root);
            }
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
            int instruction = 0;
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    if(app_categories[i].root == NULL) instruction = 1;
                    else{ instruction = 2; catNum = i;}
                }
            }
            // Case 0: No Category Exists
            if(instruction == 0){cout << "Category \"" << inputCategory << "\" not found." << endl;}
            // Case 1: Category BST is Empty
            else if(instruction ==1){cout << "Category \"" << inputCategory << "\" no apps found." << endl;}
            // Case 2: Execute Query
            else{
                cout << "Category: \"" << inputCategory <<"\""<< endl;
                print_apps_query(app_categories[catNum].root);
            }
        }
        // find price free <category>
        else if(qType == 4){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            const char *inputCategory = iCat.c_str();

            // Process Query with <inputCategory>
            int instruction = 0;
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    if(app_categories[i].root == NULL) instruction = 1;
                    else{ instruction = 2; catNum = i;}
                }
            }
            if(instruction == 0){cout << "Category \"" << inputCategory << "\" not found." << endl;}
            else if(instruction == 1){cout << "Category \"" << inputCategory << "\" no free apps found." << endl;}
            else{
                float price = 0;

                /* Implementation 1: prints list header even if the list is empty */
                cout << "Free apps in category: \"" << inputCategory <<"\""<< endl;
                printIfPrice(app_categories[catNum].root, price);

                /* Implementation 2: does not print list if no objects with the right price are found
                bool exists = findPrice(app_categories[catNum].root, price);

                if(exists){
                    cout << "Free apps in category: \"" << inputCategory <<"\""<< endl;
                    printIfPrice(app_categories[catNum].root, price);
                }
                else{
                    cout << "Category \"" << inputCategory << "\" no free apps found." << endl;
                }
                */
            }
        }
        // range <category> price <low> <high>
        else if(qType == 5){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            char *inputCategory = new char[CAT_NAME_LEN];

            if (iCat.empty()) strcpy(inputCategory, "EMPTY");
            else strcpy(inputCategory, iCat.c_str());

            // Get input low from the query
            int startOfRange = query.find('e', endOfCat+1) + 1;
            int endOfRange = query.find('\n', startOfRange+1);
            int rangeLength = endOfRange - startOfRange;
            string iRange = query.substr(startOfRange, rangeLength);

            float low, high;
            sscanf(iRange.c_str(), "%f %f", &low, &high);

            // Process Query with <inputCategory>
            int instruction = 0;
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    if(app_categories[i].root == NULL) instruction = 1;
                    else{ instruction = 2; catNum = i;}
                }
            }
            // Case 0: Category doesn't exist
            if(instruction == 0)cout << "Category \""<<inputCategory<<"\" not found."<<endl;
            // Case 1: Category BST is Empty
            else if(instruction == 1)
                {cout << "No applications found in \"" << inputCategory <<"\" for the given price range (";
                    printf("$%.2f,$%.2f).\n", low, high);}
            else{
                // Check if any objects with in this range exist
                bool exists = findInRange(app_categories[catNum].root, low, high);

                // Case 2: Print elements in the price range
                if(exists) {
                    cout << "Applications in Price Range (";
                    printf("$%.2f,$%.2f", low, high);
                    cout << ") in Category: \"" << inputCategory <<"\""<< endl;
                    print_range_in_order(app_categories[catNum].root, low, high);
                }
                // Case 3: No elements are within the price range
                else{
                    cout << "No applications found in \"" << inputCategory <<"\" for the given price range (";
                    printf("$%.2f,$%.2f).\n", low, high);
                }
            }

            delete [] inputCategory;
        }
        // range <category> name <low> <high>
        else if(qType == 6){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            char *inputCategory = new char[CAT_NAME_LEN];

            if (iCat.empty()) strcpy(inputCategory, "EMPTY");
            else strcpy(inputCategory, iCat.c_str());

            // Get input low from the query
            int startOfLow = query.find('\"',endOfCat+1) + 1;
            int endOfLow = query.find('\"',startOfLow);
            int lowLength = endOfLow - startOfLow;
            string iLow = query.substr(startOfLow, lowLength);
            const char *lowChar = iLow.c_str();

            // Get input high from the query
            int startOfHigh = query.find('\"',endOfLow+1) + 1;
            int endOfHigh= query.find('\"',startOfHigh);
            int highLength = endOfHigh - startOfHigh;
            string iHigh = query.substr(startOfHigh, highLength);
            const char *highChar = iHigh.c_str();


            // Process Query with <inputCategory>
            int instruction = 0;
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    if(app_categories[i].root == NULL) instruction = 1;
                    else{ instruction = 2; catNum = i;}
                }
            }
            // Case 0: Category doesn't exist
            if(instruction == 0)cout << "Category \""<<inputCategory<<"\" not found."<<endl;
            // Case 1: Category BST is Empty
            else if(instruction == 1)
            {cout <<"No applications found in \""<<inputCategory<<"\" for the given range ("<<lowChar<<","<<highChar<<")."<<endl;}
            else{
                bool OutOfRange = print_in_range(app_categories[catNum].root, lowChar, highChar);
                // Case 2: The entire tree is out of range
                if(OutOfRange){
                    cout << "No applications found in \"" << inputCategory <<"\" for the given range ("<<lowChar<<","<<highChar<<")."<<endl;
                }
                // Case 3: (implicit in print_in_range query call) elements within tree are in range
            }

            delete [] inputCategory;
        }
        // delete <category> <app_name>
        else if(qType == 7){
            // Get input category from the query
            int startOfCat = query.find('\"') + 1;
            int endOfCat = query.find('\"',startOfCat);
            int catLength = endOfCat - startOfCat;
            string iCat = query.substr(startOfCat, catLength);
            char *inputCategory = new char[CAT_NAME_LEN];

            if (iCat.empty()) strcpy(inputCategory, "EMPTY");
            else strcpy(inputCategory, iCat.c_str());

            // Get input app_name from the query
            int startOfName = query.find('\"',endOfCat+1) + 1;
            int endOfName = query.find('\"',startOfName);
            int nameLength = endOfName - startOfName;
            string iName = query.substr(startOfName, nameLength);
            char *inputName = new char[APP_NAME_LEN];

            if(iName.empty()) strcpy(inputName, "EMPTY");
            else strcpy(inputName, iName.c_str());


            // Check existence of category
            bool DNE = true; // Does not exist = true
            int catNum;
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category,inputCategory)==0){
                    DNE = false;
                    catNum = i;
                }
            }
            // Category doesn't exist; quit query processing
            if(DNE){
                //cout << "Application \"" << inputName << "\" not found in category \"" << inputCategory << "\"; unable to delete." << endl;
                cout << "Category \""<<inputCategory<<"\" not found."<<endl;
            }
            // Category exists; proceed with delete function
            else{
                // Deleted entry from hash table
                bool deleted = deleteEntry(hash_table, table_size, inputName, inputCategory);
                // Delete bst object from category BST
                app_categories[catNum].root = deleteNode(inputName, app_categories[catNum].root, table_size, hash_table);

                // Successful Deletion
                if(deleted){
                    cout << "Application \"" << inputName << "\" from Category \"" << inputCategory << "\" successfully deleted." << endl;
                }
                // Failed Deletion
                else{
                    cout << "Application \"" << inputName << "\" not found in category \"" << inputCategory << "\"; unable to delete." << endl;
                }
            }
            delete [] inputName;
            delete [] inputCategory;
        }
        else if(qType == 8) reportCommand = false;
        else if(qType == 9) reportCommand = true;
        // Unrecognized Query/Update
        else{
            /*
            cout << "Invalid Query #" << currQ+1 << ". Please use the following commands only:" << endl;
            cout << "\tfind app <app_name>" << endl;
            cout << "\tfind max price apps <category_name>" << endl;
            cout << "\tprint-apps category <category_name>" << endl;
            cout << "\tfind price free <category_name>" << endl;
            cout << "\trange <category_name> price <low> <high>" << endl;
            cout << "\trange <category_name> app <low> <high>" << endl;
            cout << "\tdelete <category_name> <app_name>" << endl;
            cout << "\t[no] report" << endl;
            */
        }


        // Print Spacer
        cout << endl;
        // Move to next query
        currQ++;
    }

    // Deallocate Queries
    for(int i=0; i<q; i++) delete [] queries[i];


    // Report Output
    if(reportCommand || 1){
        // Creat new file for outputting statistics
        string outFileName = "report.txt";
        ofstream out;
        out.open(outFileName);
        // BST STATISTICS:
        out << "BST Statistics" << endl;
        out << "\tNumber of Categories: " << numCategories << endl;
        for (int i=0; i<numCategories; i++){
            out << "\t" << app_categories[i].category << endl;

            int totalCount = count(app_categories[i].root);
            out << "\t\tTotal Nodes: " << totalCount << endl;

            int height = heightTree(app_categories[i].root);
            out << "\t\tHeight: " << height << endl;

            if(totalCount == 0){
                out << "\t\tNo Nodes Exist." << endl;
            }
            else if(height == 0){
                out << "\t\tNo Subtrees Exist." << endl;
            }
            else{
                int heightL = heightTree(app_categories[i].root->left);
                out << "\t\tHeight of Left Subtree: " << heightL << endl;

                int heightR = heightTree(app_categories[i].root->right);
                out << "\t\tHeight of Right Subtree: " << heightR << endl;
            }
        }


        // HASH TABLE STATISTICS:
        out << "\nHash Table Statistics" << endl;
        double hash_m = table_size;
        double hash_n = 0;           // should equal numApps
        int chainLength [numApps+1]; // Stores one length value per possible number of apps per linked list; Range:(0,numApps)
        int maxLength;
        // Fill lengthArray with the number of lists per length l, 0<l<m
        for(int i=0; i<=numApps; i++){ // m = # of applications (local variable)
            chainLength[i] = listsWithLength(hash_table, table_size, i);

            // Reset maxLength if applicable
            if(chainLength[i] > 0) maxLength = i;
        }
        // Print Length Data
        out << "\tChain Length\t# of Lists" << endl;
        for(int length=0; length<=maxLength; length++){
            out << "\t\t" << length << "\t\t" << chainLength[length] << endl;

            hash_n = hash_n + length*chainLength[length];
        }
        out << "\tMax Length = " << maxLength << endl;
        out << "\tn = " << hash_n << endl;
        out << "\tm = " << hash_m << endl;
        double alpha = hash_n/hash_m;
        out << setprecision(3) << "\tLoad Factor = " << alpha << endl;



        // RUNNING TIME ANALYSIS
        // find app <app_name> - hash v. BST running time comparison
        // Clock function code inspired by https://www.geeksforgeeks.org/measure-execution-time-function-cpp/

        // Set Arbitrary app_name to search
        char *query_name = new char[APP_NAME_LEN];

        // Get name from random entry in table
        int tableIndex = 0;
        hash_table_entry *randEntry = hash_table[tableIndex];
        while(tableIndex < hash_m-1 && randEntry == NULL) {
            tableIndex++;
            randEntry = hash_table[tableIndex];
        }
        // If the entire hash table is empty, conduct unsuccessful search
        if(randEntry == NULL) strcpy(query_name, "Random Name App");
        // Conduct successful search on random app name
        else strcpy(query_name, randEntry->app_name);

        out << "\nfind app \"" << query_name << "\" Running Time Comparison:" << endl;


        // Hash Table Running Time:
        auto start = std::chrono::system_clock::now();
        bst* hash_return = searchHashTable(hash_table, query_name, table_size);
        auto end = std::chrono::system_clock::now();
        auto hash_time = std::chrono::duration<double, nano>(end-start);

        // Extract category from hash table entry to use in BST search
        char *category = NULL;
        if(hash_return != NULL) category = hash_return->record.category;

        // BST Running Time:
        auto start2 = std::chrono::system_clock::now();

        int categoryIndex = -1;
        if(category != NULL){
            for(int i=0; i<numCategories; i++){
                if(strcmp(app_categories[i].category, category) == 0) categoryIndex = i;
            }
        }

        bst *bst_return = NULL;
        if(categoryIndex == -1) categoryIndex = 0; // Conduct unsuccessful search if category doesn't exist
        bst_return = searchNode(query_name, app_categories[categoryIndex].root);

        auto end2 = std::chrono::system_clock::now();
        auto bst_time = std::chrono::duration<double, nano>(end2-start2);

        // Print Results
        if(bst_return == NULL) out << "\tUnsuccessful Search:" << endl;
        else out << "\tSuccessful Search:" << endl;
        out << "\tHash Table Running Time: " << hash_time.count() << " nanoseconds" << endl;
        out << "\tBinary Search Tree Running Time: " << bst_time.count() << " nanoseconds" << endl;

        delete [] query_name;
        out.close();
    }




    // Free Memory and Exit
    //      BST
    for(int i=0; i<numCategories; i++){
        if(app_categories[i].root != NULL) app_categories[i].root = deleteTree(app_categories[i].root);
        delete [] app_categories[i].root;
    }
    delete [] app_categories;
    //      Hash Table
    for(int j=0; j<table_size; j++){
        while(hash_table[j] != NULL){
            hash_table_entry *tempEntry = hash_table[j];

            hash_table[j] = hash_table[j]->next;

            delete [] tempEntry;
        }
        delete [] hash_table[j];
    }
    delete [] hash_table;

    return 0;
}