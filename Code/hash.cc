#include <iostream>
#include <cstring>
#include <cmath>
#include "Headers/prime.h"
#include "Headers/bst.h"

/* countAt (int i)
 * Counts the number of elements in a given linked list pointed to by the hash table */
int countAt (hash_table_entry *head){
    int count = 0;
    while(head != NULL){
        count ++;
        head = head->next;
    }
    return count;
}

/* listsWithLength
 * Returns the number of lists with linked list length (int length) */
int listsWithLength(hash_table_entry **table, int table_size, int length){
    int count = 0;
    for(int i=0; i<table_size; i++){
        if(countAt(table[i]) == length) count ++;
    }
    return count;
}

/* getHTSize
 * Description: computes the size of the hash table for a given number of elements m */
int getHTSize(int m){
    int k = firstPrime(2*m);
    return k;
}

/* h - hash function
 * Hashes an app's name to a position in the hash table. */
int h(char *name, int m){
    int k; // return value = sum(char[]) mod m

    // Get sum
    int sum = 0;
    int i = 0;
    char c = name[i];
    while(c != '\0'){
        int val = c;
        sum = sum + val;
        i++;
        c = name[i];
    }
    // Compute remainder of sum / table size
    k = (int)fmod(sum, m);
    return k;
}

/* insertHash
 * Description: inserts a new BST object into a row of the hash table. */
bool insertHash(hash_table_entry **table, bst *obj, int table_size){
    int table_position = h(obj->record.app_name, table_size);

    // Create New Table Entry Object and attach BST
    hash_table_entry *newEntry = new hash_table_entry[sizeof(hash_table_entry)];
    newEntry->app_node = obj;
    strcpy(newEntry->app_name, obj->record.app_name);

    // Insert at HEAD of Linked List
    newEntry->next = table[table_position];
    table[table_position] = newEntry;

    return true;
}

/* Query - find app <app_name>
 * Description: Returns the binary search tree pointer corresponding to the app_name.*/
bst * searchHashTable(hash_table_entry ** table, char *name, int table_size){
    int position = h(name, table_size);
    // Case 0: Not Found - no entries at the position in the table
    if(table[position] == NULL) return NULL;
    // Case 1: Search Row for the app name
    else{
        hash_table_entry *finder = table[position];
        // Search Row until
        while(finder != NULL && strcmp(finder->app_name, name) != 0){
            finder = finder->next;
        }
        // Case 1.1: Not Found - reached end of linked list
        if(finder == NULL) return NULL;
        // Case 1.2: Found - return the BST at the linked list node
        else{
            return finder->app_node;
        }
    }
}

/* printAllAt
 * Description: prints all app names of the entries at a given row in the hash table */
void printAllAt(hash_table_entry **table, int index){
    hash_table_entry *entry = table[index];
    while(entry != NULL){
        std::cout << entry->app_name << std:: endl;
        entry = entry->next;
    }
}

/* deleteEntry
 * Uses hash function to find table index, then conducts linear search on linked list */
bool deleteEntry(hash_table_entry **table, int table_size, char *name, char *category){
    int position = h(name, table_size);

    hash_table_entry *finder = table[position];
    // Case 0: No entries at table[position];
    if(finder == NULL) return false;
    // Case 1: The first entry matches (both name and category)
    else if(strcmp(finder->app_name, name) == 0 && strcmp(finder->app_node->record.category, category) == 0){
        // Set Head to finder.next
        table[position] = finder->next;
        delete [] finder;
        return true;
    }
    // Case 2: the first entry does not match, search linked list
    else{
        // Iterate until finder.next matches or end-of-list reached
        while(finder->next!=NULL && !(strcmp(finder->next->app_name, name)==0 && strcmp(finder->next->app_node->record.category, category)==0)){
            finder = finder->next;
        }
        // Case 2.1: End-of-list, not found
        if(finder->next == NULL) return false;
        // Case 2.2: Delete finder->next
        else{
            hash_table_entry *found = finder->next;
            // Set finder.next (remove pointer to found from linked list)
            finder->next = found->next;
            // Delete hash_table_entry
            delete [] found;
            found = NULL;

            return true;
        }
    }
}