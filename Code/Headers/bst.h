//
// Created by wgrie on 2/24/2021.
//

#ifndef CSE310_P2_BST_H
#define CSE310_P2_BST_H
#include "hash.h"
bst * insertBST(bst *root, bst *obj);
int count(bst *root);
bst * deleteTree(bst *root);
bst * deleteNode(char *key, bst *root, int table_size, hash_table_entry **table);
bst * searchNode(char *key, bst *root);
int heightTree(bst *root);
int left  (int p);
int right (int p);
void InOrderTraversal(bst *root);
#endif //CSE310_P2_BST_H