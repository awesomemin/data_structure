#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _Vertex {
  int id;
  struct _Vertex *next;
} Vertex;

typedef struct _Graph {
  int size;
  Vertex **heads;
} Graph;

Graph* createGraph(int size);
void removeGraph(Graph *G);
void addEdge(Graph *G, int u, int v);
void printGraph(Graph *G);

void DFS(Graph *G);
void BFS(Graph *G);

int main() {
  Graph *G = createGraph(8);
  addEdge(G, 0, 1);
  addEdge(G, 0, 2);
  addEdge(G, 0, 7);
  addEdge(G, 1, 3);
  addEdge(G, 1, 5);
  addEdge(G, 1, 7);
  addEdge(G, 2, 5);
  addEdge(G, 2, 6);
  addEdge(G, 3, 4);
  addEdge(G, 3, 7);
  addEdge(G, 4, 7);
  addEdge(G, 5, 7);
  addEdge(G, 6, 7);
  printGraph(G);
  DFS(G);
  BFS(G);
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

void appendVertex(Vertex *head, int id) {
  // Write your own code
  // Append the vertex at the last of the linked list
  while(head->next != NULL) {
    head = head->next;
  }
  head->next = (Vertex*)malloc(sizeof(Vertex));
  head->next->id = id;
  head->next->next = NULL;
}

void addEdge(Graph *G, int u, int v) {
  appendVertex(G->heads[u], v); // add an edge from u to v
  appendVertex(G->heads[v], u); // add an edge from v to u
}

void printGraph(Graph *G) {
  Vertex *v;
  for (int i = 0; i < G->size; i ++) {
    printf("%d: ", i);
    v = G->heads[i]->next;
    while (v != NULL) {
      printf("%d ", v->id);
      v = v->next;
    }
    printf("\n");
  }
}

void DFS(Graph *G) {
  // Create an array for visiting marks & a stack for vertex nodes
  bool *visited = (bool *)malloc(sizeof(bool) * G->size);
  Vertex **stack = (Vertex **)malloc(sizeof(Vertex *) * G->size);
  int top = -1;

  for (int i = 0; i < G->size; i ++) visited[i] = false;

  // Write your own code
  // Depth-first search (DFS) using stack
  // - Start from the vertex 0
  // - Check the next neighbor of the top vertex in the stack
  // - If the neighbor is not visited yet, then push the neighbor
  // - Otherwise, ignore it
  stack[++top] = G->heads[0];
  visited[0] = true;
  printf("DFS: %d ", 0);
  while(top >= 0) {
    stack[top] = stack[top]->next; // 스택 맨 위를 꺼내고, 스택 맨 위 꼭지점의 다음 꼭짓점 삽입
    if(stack[top] == NULL) {
      top--;
      continue;;
    }
    int nextId = stack[top]->id;
    if(!visited[nextId]) {
      visited[nextId] = true;
      stack[++top] = G->heads[nextId];
      printf("%d ", nextId);
    }
  }
  printf("\n");

  free(visited);
  free(stack);
}

void BFS(Graph *G) {
  // Create an array for visiting marks & a queue for vertex nodes
  bool *visited = (bool *)malloc(sizeof(bool) * G->size);
  Vertex **queue = (Vertex **)malloc(sizeof(Vertex *) * G->size);
  int front = 0, rear = 0;

  for (int i = 0; i < G->size; i ++) visited[i] = false;

  // Write your own code
  // Breadth-first search (BFS) using queue
  // - Start from the vertex 0
  // - Check the next neighbor of the front vertex in the queue
  // - If the neighbor is not visited yet, then enqueue the neighbor
  // - Otherwise, ignore it
  queue[rear++] = G->heads[0];
  visited[0] = true;
  printf("BFS: %d ", 0);
  while(front < rear) {
    queue[front] = queue[front]->next;
    if(queue[front] == NULL) {
      front++;
      continue;
    }
    int nextId = queue[front]->id;
    if (!visited[nextId]) {
      queue[rear++] = G->heads[nextId];
      visited[nextId] = true;
      printf("%d ", nextId);
    }
  }
  printf("\n");

  free(visited);
  free(queue);
}
