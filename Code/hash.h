//
// Created by wgrie on 2/25/2021.
//

#ifndef CSE310_P2_HASH_H
#define CSE310_P2_HASH_H
#include "bst.h"
int countAt(hash_table_entry *head);
int listsWithLength(hash_table_entry **table, int table_size, int length);
int getHTSize(int m);
int h(char *name);
bool insertHash(hash_table_entry **table, bst *obj);
bst * searchHashTable(hash_table_entry ** table, char *name);
bool deleteEntry(hash_table_entry **table, char *name, char *category);
void printAllAt(hash_table_entry **table, int index);
#endif //CSE310_P2_HASH_H
