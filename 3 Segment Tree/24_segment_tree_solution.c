#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct _SegmentTree {
  int nodes[2*MAX_SIZE+1];
  int size;
} SegmentTree;

int max(int a, int b);
void construct(int items[], int n, SegmentTree *tree);
void update(SegmentTree *tree, int item, int index);
int computeMax(SegmentTree *tree, int left, int right);
void print(SegmentTree *tree);

int main() {
  int items[9] = { 0, 5, 6, 1, 3, 8, 2, 7, 4 }, n = 8;
  SegmentTree tree;
  construct(items, n, &tree);
  print(&tree);

  printf("max between %d and %d elements: %d\n", 1, 4, computeMax(&tree, 1, 4));
  printf("max between %d and %d elements: %d\n", 2, 5, computeMax(&tree, 2, 5));
  printf("max between %d and %d elements: %d\n", 6, 8, computeMax(&tree, 6, 8));

  update(&tree, 9, 3);
  print(&tree);
  printf("max between %d and %d elements: %d\n", 1, 4, computeMax(&tree, 1, 4));
  printf("max between %d and %d elements: %d\n", 2, 5, computeMax(&tree, 2, 5));
  printf("max between %d and %d elements: %d\n", 6, 8, computeMax(&tree, 6, 8));
  return 0;
}

int max(int a, int b) {
  return a > b ? a : b;
}

void construct(int items[], int n, SegmentTree *tree) {
  // Write your own code
  // 1. count # of leaf nodes
  int numLeafs = 1;
  while (numLeafs < n) numLeafs *= 2;
  tree->size = numLeafs*2 - 1;

  // 2. initialize leaf nodes
  int i;
  for (i = 1; i <= n; i ++)
    tree->nodes[numLeafs + i -1] = items[i];
  for (i = n+1; i <= numLeafs; i ++)
    tree->nodes[numLeafs + i -1] = 0;

  // 3. initialize internal nodes
  for (i = numLeafs-1; i >= 1; i --)
    tree->nodes[i] = max(tree->nodes[i*2], tree->nodes[i*2+1]);
}

void update(SegmentTree *tree, int item, int index) {
  // Write your own code
  // 1. convert the array index to tree index
  index = tree->size / 2 + index;

  // 2. update the leaf node
  tree->nodes[index] = item;

  // 3. update its ancestors
  for (index = index / 2; index >= 1; index /= 2) {
    tree->nodes[index] = max(tree->nodes[index*2], tree->nodes[index*2+1]);
  }
}

int computeMax(SegmentTree *tree, int left, int right) {
  // Write your own code

  // 1. convert the array indices to tree indices
  left += tree->size / 2;
  right += tree->size / 2;

  // 2. find representative nodes
  int result = 0;
  while (left <= right) {
    if (left % 2 == 1) result = max(result, tree->nodes[left]);
    if (right % 2 == 0) result = max(result, tree->nodes[right]);
    left = (left + 1) / 2;
    right = (right - 1) / 2;
  }
  return result;
}

void print(SegmentTree *tree) {
  printf("tree: ");
  for (int i = 1; i <= tree->size; i ++) printf("%d ", tree->nodes[i]);
  printf("\n");
}
