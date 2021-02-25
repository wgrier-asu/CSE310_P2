//
// Created by wgrie on 2/24/2021.
//

#ifndef CSE310_P2_BST_H
#define CSE310_P2_BST_H
#include "defn.h"

bst * insertBST(bst *root, app_info *info);
int count(bst *root);
void deleteTree(bst *root);
int left  (int p);
int right (int p);
int parent(int p);


#endif //CSE310_P2_BST_H