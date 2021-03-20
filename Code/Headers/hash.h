//
// Created by wgrie on 2/25/2021.
//

#ifndef CSE310_P2_HASH_H
#define CSE310_P2_HASH_H
#include "defn.h"
int countAt(hash_table_entry *head);
int listsWithLength(hash_table_entry **table, int table_size, int length);
int getHTSize(int m);
int h(char *name, int m);
bool insertHash(hash_table_entry **table, bst *obj, int table_size);
bst * searchHashTable(hash_table_entry ** table, char *name, int table_size);
bool deleteEntry(hash_table_entry **table, int table_size, char *name, char *category);
void printAllAt(hash_table_entry **table, int index);
void rehash(bst *x, int table_size, hash_table_entry **table);
#endif //CSE310_P2_HASH_H
