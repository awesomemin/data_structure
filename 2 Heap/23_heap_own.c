#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct _MaxHeap {
  int items[MAX_SIZE+1]; // 실제 트리를 담을 배열, index 0은 비워두고 1부터 시작한다.
  int size; // 현재 노드의 개수
} MaxHeap;

void swap(int *a, int *b); // a index와 b index를 교환
int getFirst(MaxHeap *heap); // root node의 값을 반환
void insert(MaxHeap *heap, int item); // 새 노드를 삽입
void delete(MaxHeap *heap); // 루트 노드를 삭제
void print(MaxHeap *heap); // 트리 출력

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
  int newNodePosition = heap->size + 1; // 새 노드가 들어갈 index : 가장 마지막 자리
  heap->items[newNodePosition] = item; // 가장 마지막 자리에 새 노드 삽입
  while(heap->items[newNodePosition / 2] <= heap->items[newNodePosition]) {
    // 자식이 부모보다 크면 반복
    swap(&heap->items[newNodePosition / 2], &heap->items[newNodePosition]);
    newNodePosition = newNodePosition / 2;
    if(newNodePosition == 1) break; // 새 노드가 루트 자리에 올라가면 반복 해제제
  }

  heap->size++;
}

void delete(MaxHeap *heap) {
  // Write your own code
  // 1. Swap the root node X and the last node Y.
  // 2. Delete the node X.
  // 3. Compare the node Y with its children L and R. 
  // 3a. If Y has a higher priority than L and R, nothing to do.
  // 3b. If L has a higher priority than Y and R, swap L and Y, and then repeat at the new position of Y.
  // 3c. If R has a higher priority than Y and L, swap R and Y, and then repeat at the new position of Y.
  swap(&heap->items[1], &heap->items[heap->size]);
  heap->size--;
  int newRootPosition = 1;
  // 1. have 2 children
  // 2. have 1 (left child)
  // 3. have no child
  if(newRootPosition * 2 > heap->size) {
    // no child, do nothing
  }
  else if(newRootPosition * 2 == heap->size) {
    // only left child
    if(heap->items[newRootPosition] < heap->items[newRootPosition * 2]) {
      swap(&heap->items[newRootPosition], &heap->items[newRootPosition * 2]);
      newRootPosition = newRootPosition * 2;
    }
  }
  else if(newRootPosition * 2 + 1 <= heap->size) {
    // have two children
    while(heap->items[newRootPosition] < heap->items[newRootPosition * 2] || heap->items[newRootPosition] < heap->items[newRootPosition * 2 + 1]) {
      int swapTargetChild = (heap->items[newRootPosition * 2] > heap->items[newRootPosition * 2 + 1]) ? (newRootPosition * 2) : (newRootPosition * 2 + 1);
      swap(&heap->items[newRootPosition], &heap->items[swapTargetChild]);
      newRootPosition = swapTargetChild;
      if(newRootPosition * 2 == heap->size) {
        // only left child exist
        if(heap->items[newRootPosition] < heap->items[newRootPosition * 2]) {
          swap(&heap->items[newRootPosition], &heap->items[newRootPosition * 2]);
        }
        break;
      }
      else if(newRootPosition * 2 > heap->size) {
        // no child
        break;
      }
    }
  }
}

void print(MaxHeap *heap) {
  printf("heap: ");
  for (int i = 1; i <= heap->size; i ++) printf("%d ", heap->items[i]);
  printf("\n");
}

// heap: 10 8 9 5 4 7 3 2 1 3 0 6 
// heap: 12 8 10 5 4 9 3 2 1 3 0 6 7 
// heap: 12 8 11 5 4 9 10 2 1 3 0 6 7 3 
// heap: 11 8 10 5 4 9 3 2 1 3 0 6 7 