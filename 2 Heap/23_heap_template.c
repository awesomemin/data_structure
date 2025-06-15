#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct _MaxHeap {
  int items[MAX_SIZE+1];
  int size;
} MaxHeap;

void swap(int *a, int *b);
int getFirst(MaxHeap *heap);
void insert(MaxHeap *heap, int item);
void delete(MaxHeap *heap);
void print(MaxHeap *heap);

int main() {
  MaxHeap heap;
  heap.size = 0;
  insert(&heap, 10);
  insert(&heap, 8);
  insert(&heap, 9);
  insert(&heap, 5);
  insert(&heap, 4);
  insert(&heap, 7);
  insert(&heap, 3);
  insert(&heap, 2);
  insert(&heap, 1);
  insert(&heap, 3);
  insert(&heap, 0);
  insert(&heap, 6);
  print(&heap);

  insert(&heap, 12);
  print(&heap);

  insert(&heap, 11);
  print(&heap);

  delete(&heap);
  print(&heap);
  return 0;
}

void swap(int *a, int *b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int getFirst(MaxHeap *heap) {
  return heap->items[1];
}

void insert(MaxHeap *heap, int item) {
  // Write your own code
  // 1. Insert new item at the last position
  // 2. Compare the new item X with its parent P
  // 2a. If X has a higher priority than P, swap X and P, and then repeat Step 2 at the new position of X.
  // 2b. If X has a lower priority than P, stop the iteration.
}

void delete(MaxHeap *heap) {
  // Write your own code
  // 1. Swap the root node X and the last node Y.
  // 2. Delete the node X.
  // 3. Compare the node Y with its children L and R. 
  // 3a. If Y has a higher priority than L and R, nothing to do.
  // 3b. If L has a higher priority than Y and R, swap L and Y, and then repeat at the new position of Y.
  // 3c. If R has a higher priority than Y and L, swap R and Y, and then repeat at the new position of Y.
}

void print(MaxHeap *heap) {
  printf("heap: ");
  for (int i = 1; i <= heap->size; i ++) printf("%d ", heap->items[i]);
  printf("\n");
}
