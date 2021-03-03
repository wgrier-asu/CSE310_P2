//
// Created by wgrie on 2/24/2021.
//

#ifndef CSE310_P2_HEAP_H
#define CSE310_P2_HEAP_H
float Max(float *heap);
void maxHeapify(float *heap, int pos, int size);
float * buildMaxHeap(float *heap, int size);
#endif //CSE310_P2_HEAP_H
