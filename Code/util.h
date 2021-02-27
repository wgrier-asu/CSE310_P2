//
// Created by wgrie on 2/24/2021.
//

#ifndef CSE310_P2_UTIL_H
#define CSE310_P2_UTIL_H
#include <string>
#include "bst.h"

void print_app_names_in_order(bst *root);
void print_apps_query(bst *root);
int allocatePriceHeap(float *heap, int size, int pos, bst *root);
void printIfPrice(bst *root, float priceKey);
void find_max_price_query(bst *root);
bool print_in_range(bst *root, char low, char high);
bool print_in_range(bst *root, float low, float high);
int getQType(std::string query, int qLength);
void printAppInfo(app_info *info);
void printAppInfo(app_info info);
#endif //CSE310_P2_UTIL_H
