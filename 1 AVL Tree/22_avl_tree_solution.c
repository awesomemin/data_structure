#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _Node {
  int key, height;
  struct _Node *left, *right;
} Node;

Node* createLeaf(int key);
void removeTree(Node *root);
int getHeight(Node *node);
void updateHeight(Node *node);
int computeBalanceFactor(Node *node);
void traverse(Node *node); // in-order traversal

Node* LLRotation(Node *root);
Node* RRRotation(Node *root);
Node* LRRotation(Node *root);
Node* RLRotation(Node *root);
Node* updateNode(Node *root);

bool isAVL(Node *node, int min, int max);
Node* insertNode(int key, Node *root);
Node* deleteNode(int key, Node *root);

int main() {
  Node *root = createLeaf(8);
  root = insertNode(4, root);
  root = insertNode(12, root);
  root = insertNode(2, root);
  root = insertNode(5, root);
  root = insertNode(9, root);
  root = insertNode(15, root);
  root = insertNode(1, root);
  root = insertNode(3, root);
  root = insertNode(10, root);
  root = insertNode(13, root);
  root = insertNode(17, root);

  printf("0. Basic information:\n");
  printf("Height: %d\n", getHeight(root));
  printf("In-order traversal: ");
  traverse(root);
  printf("\n");
  printf("\n");

  printf("1. Check validity of AVL:\n");
  if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
  else printf("This tree is not a AVL tree\n");
  printf("\n");

  printf("2. Insert 11 into AVL:\n");
  insertNode(11, root);
  printf("root->right->left->key: %d\n", root->right->left->key);
  printf("root->right->left->left->key: %d\n", root->right->left->left->key);
  printf("root->right->left->right->key: %d\n", root->right->left->right->key);
  printf("In-order traversal in new AVL: ");
  traverse(root);
  printf("\n");
  if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
  else printf("This tree is not a AVL tree\n");
  printf("\n");

  printf("3. Delete 5 from BST:\n");
  root = deleteNode(5, root);
  printf("root->left->key: %d\n", root->left->key);
  printf("root->left->left->key: %d\n", root->left->left->key);
  printf("root->left->right->key: %d\n", root->left->right->key);
  printf("root->left->right->left->key: %d\n", root->left->right->left->key);
  printf("In-order traversal in new BST: ");
  traverse(root);
  printf("\n");
  if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
  else printf("This tree is not a AVL tree\n");
  printf("\n");

  removeTree(root);
  return 0;
}

Node* createLeaf(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

void removeTree(Node *root) {
  if (root == NULL) return;
  removeTree(root->left);
  removeTree(root->right);
  free(root);
}

int getHeight(Node *node) {
  // write your own code
  if (node == NULL) return 0;
  return node->height;
}

void updateHeight(Node *node) {
  // write your own code
  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);
  node->height = leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
}

int computeBalanceFactor(Node *node) {
  // write your own code
  return getHeight(node->left) - getHeight(node->right);
}

void traverse(Node *node) {
  if (node == NULL) return;
  traverse(node->left);
  printf("%d ", node->key);
  traverse(node->right);
}

// Check all keys in the subtree are in the (min,max) interval
bool isAVL(Node *root, int min, int max) {
  if (root == NULL) return true;
  int balanceFactor = computeBalanceFactor(root);
  bool checkRoot = (min < root->key && root->key < max && balanceFactor >= -1 && balanceFactor <= 1);
  bool checkLeft = isAVL(root->left, min, root->key);
  bool checkRight = isAVL(root->right, root->key, max);
  return checkRoot && checkLeft && checkRight;
}

// This returns the root after insertion
Node* insertNode(int key, Node *root) {
  if (root == NULL) return createLeaf(key);
  if (key < root->key) root->left = insertNode(key, root->left);
  else root->right = insertNode(key, root->right);

  root = updateNode(root);
  return root;
}

// This returns the root after deletion
Node* deleteNode(int key, Node *root) {
  if (key < root->key)
    root->left = deleteNode(key, root->left);
  else if (key > root->key)
    root->right = deleteNode(key, root->right);
  else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
      return root;
    }
    else if (root->left == NULL || root->right == NULL) {
      Node *child = root->left != NULL ? root->left : root->right;
      free(root);
      root = child;
      return child;
    }
    else {
      Node *successor = root->right;
      while (successor->left != NULL)
        successor = successor->left;
      root->key = successor->key;
      root->right = deleteNode(successor->key, root->right);
    }
  }

  root = updateNode(root);
  return root;
}

Node* LLRotation(Node *root) {
  // write your own code
  Node *left = root->left;
  root->left = left->right;
  left->right = root;
  updateHeight(root);
  updateHeight(left);
  return left;
}

Node* RRRotation(Node *root) {
  // write your own code
  Node *right = root->right;
  root->right = right->left;
  right->left = root;
  updateHeight(root);
  updateHeight(right);
  return right;
}

Node* LRRotation(Node *root) {
  // write your own code
  Node *left = root->left; // B
  Node *leftright = left->right; // D
  left->right = leftright->left; // DL
  root->left = leftright->right; // DR
  leftright->left = left;
  leftright->right = root;
  updateHeight(root);
  updateHeight(left);
  updateHeight(leftright);
  return leftright;
}

Node* RLRotation(Node *root) {
  // write your own code
  Node *right = root->right; // C
  Node *rightleft = right->left; // D
  right->left = rightleft->right; // DR
  root->right = rightleft->left; // DL
  rightleft->left = root;
  rightleft->right = right;
  updateHeight(root);
  updateHeight(right);
  updateHeight(rightleft);
  return rightleft;
}

// This returns the root after update
Node* updateNode(Node *root) {
  // write your own code
  updateHeight(root);
  int balanceFactor = computeBalanceFactor(root);
  if (balanceFactor == 2) {
    if (computeBalanceFactor(root->left) >= 0)
      root = LLRotation(root);
    else
      root = LRRotation(root);
  }
  else if (balanceFactor == -2) {
    if (computeBalanceFactor(root->right) <= 0)
      root = RRRotation(root);
    else
      root = RLRotation(root);
  }
  return root;
}
