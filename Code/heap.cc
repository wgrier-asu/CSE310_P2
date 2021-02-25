#include <cmath>
#include "bst.h"

float Max(float *heap){
    float max = heap[0];
    if(max<0.01) max = 0.0;
    return max;
}

void maxHeapify(float *heap, int pos, int size){
    int l = left(pos)-1;
    int r = right(pos)-1;
    pos--;
    // Note: subtraction is to adjust index from [1..n] to [0..n-1]

    // Find the largest value's position
    int largest = pos;
    if(l <= size && heap[l] > heap[largest]){
        largest = l;
    }
    if(r <= size && heap[r] > heap[largest]){
        largest = r;
    }

    // Swap if current object is not the largest
    if(largest != pos){
        float temp = heap[pos];
        heap[pos] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, largest+1, size);
    }
}


float * buildMaxHeap(float *heap, int size){
    int firstParent = floor(size/2);
    for(int i=firstParent; i>0; i--){
        maxHeapify(heap, i, size);
    }
    return heap;
}