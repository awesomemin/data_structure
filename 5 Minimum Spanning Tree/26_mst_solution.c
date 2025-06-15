#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _Vertex {
  int id, weight;
  struct _Vertex *next;
} Vertex;

typedef struct _Graph {
  int size;
  Vertex **heads;
} Graph;

Graph* createGraph(int size);
void removeGraph(Graph *G);
void addEdge(Graph *G, int u, int v, int weight);
void printGraph(Graph *G);

void Prim(Graph *G);
void Dijkstra(Graph *G, int s, int e);

int main() {
  Graph *G = createGraph(7);
  addEdge(G, 0, 1, 2);
  addEdge(G, 0, 5, 15);
  addEdge(G, 1, 3, 14);
  addEdge(G, 2, 3, 12);
  addEdge(G, 2, 4, 8);
  addEdge(G, 2, 5, 5);
  addEdge(G, 3, 4, 10);
  addEdge(G, 4, 6, 4);
  addEdge(G, 5, 6, 6);
  printGraph(G);
  Prim(G);
  free(G);
  return 0;
}

Graph* createGraph(int size) {
  Graph *G = (Graph *)malloc(sizeof(Graph *));
  G->size = size;
  G->heads = (Vertex **)malloc(sizeof(Vertex *) * size);
  for (int i = 0; i < size; i ++) {
    // dummy node
    G->heads[i] = (Vertex *)malloc(sizeof(Vertex));
    G->heads[i]->next = NULL;
  }
  return G;
}

void removeGraph(Graph *G) {
  Vertex *tmp;
  for (int i = 0; i < G->size; i ++) {
    while (G->heads[i] != NULL) {
      tmp = G->heads[i];
      G->heads[i] = G->heads[i]->next;
      free(tmp);
    }
  }
  free(G->heads);
  free(G);
}

void appendVertex(Vertex *head, int id, int weight) {
  // append the vertex at the last of the linked list
  while (head->next != NULL) head = head->next;
  head->next = (Vertex *)malloc(sizeof(Vertex));
  head->next->id = id;
  head->next->weight = weight;
  head->next->next = NULL;
}

void addEdge(Graph *G, int u, int v, int weight) {
  appendVertex(G->heads[u], v, weight); // add an edge from u to v
  appendVertex(G->heads[v], u, weight); // add an edge from v to u
}

void printGraph(Graph *G) {
  Vertex *v;
  for (int i = 0; i < G->size; i ++) {
    printf("%c: ", 'A' + i);
    v = G->heads[i]->next;
    while (v != NULL) {
      printf("%c(%d) ", 'A' + v->id, v->weight);
      v = v->next;
    }
    printf("\n");
  }
}

typedef struct _SegmentNode {
  int id, weight;
} SegmentNode;

typedef struct _SegmentTree {
  int size;
  SegmentNode *nodes;
} SegmentTree;

SegmentTree* createSegmentTree(int size) {
  int numLeafs = 1;
  while (numLeafs < size) numLeafs *= 2;

  SegmentTree *tree = (SegmentTree *)malloc(sizeof(SegmentTree));
  tree->size = numLeafs * 2 - 1;
  tree->nodes = (SegmentNode *)malloc(sizeof(SegmentNode) * (numLeafs*2-1));
  for (int i = 1; i <= numLeafs; i ++) {
    tree->nodes[tree->size/2+i].id = i;
    tree->nodes[tree->size/2+i].weight = INT_MAX;
  }
  for (int i = 1; i < numLeafs; i ++) {
    tree->nodes[i].id = 1;
    tree->nodes[i].weight = INT_MAX;
  }
  return tree;
}

void removeSegmentTree(SegmentTree *tree) {
  free(tree->nodes);
  free(tree);
}

void updateSegmentTree(SegmentTree *tree, int id, int weight) {
  // Write your own code
  int idx = tree->size/2+id;
  if (tree->nodes[idx].weight == INT_MAX-1) // if the node is already inserted
    return;

  if (tree->nodes[idx].weight > weight || weight == INT_MAX-1)
    tree->nodes[idx].weight = weight;
  for (idx /= 2; idx >= 1; idx /= 2) {
    if (tree->nodes[idx*2].weight < tree->nodes[idx*2+1].weight)
      tree->nodes[idx] = tree->nodes[idx*2];
    else
      tree->nodes[idx] = tree->nodes[idx*2+1];
  }
}

void Prim(Graph *G) {
  // Write your own code
  // 1. Create a segment tree
  Vertex *v;
  SegmentNode node;
  SegmentTree *tree = createSegmentTree(G->size);
  int cost = 0;

  printf("\nPrim:\n");
  
  // 2. Insert the starting vertex
  updateSegmentTree(tree, 1, 0);

  // 3. Prim's algorithm
  for (int n = 1; n <= G->size; n++) {
    node = tree->nodes[1];
    printf("%c(%d)\n", 'A' + node.id - 1, node.weight);
    cost += node.weight;

    updateSegmentTree(tree, node.id, INT_MAX-1); // mark the node as inserted

    v = G->heads[node.id-1]->next;
    while (v != NULL) {
      updateSegmentTree(tree, v->id+1, v->weight);
      v = v->next;
    }
  }
  printf("minimum cost: %d\n", cost);
  removeSegmentTree(tree);
}
