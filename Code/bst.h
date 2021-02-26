//
// Created by wgrie on 2/24/2021.
//

#ifndef CSE310_P2_BST_H
#define CSE310_P2_BST_H
#include "defn.h"

bst * insertBST(bst *root, bst *obj);
int count(bst *root);
void deleteTree(bst *root);
void deleteNode(bst *node);
int heightTree(bst *root);
int left  (int p);
int right (int p);
int parent(int p);


#endif //CSE310_P2_BST_H