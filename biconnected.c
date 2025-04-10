#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
int time_counter = 0;
int component_no = 0;
typedef struct {
 int u, v;
} Edge;
typedef struct {
 Edge edges[MAX];
 int top;
} Stack;
void push(Stack *stack, int u, int v) {
 stack->edges[++stack->top] = (Edge){u, v};
}

Edge pop(Stack *stack) {
 return stack->edges[stack->top--];
}
void findBCCUtil(int u, int disc[], int low[], int parent[], bool visited[], Stack *stack, int adj[MAX][MAX], int V) {
 int children = 0;
 visited[u] = true;
 disc[u] = low[u] = ++time_counter;
int v;
 for (v = 0; v < V; v++) {
 if (adj[u][v]) {
 if (!visited[v]) {
 children++;
 parent[v] = u;
 push(stack, u, v);
 findBCCUtil(v, disc, low, parent, visited, stack, adj, V);
 low[u] = (low[u] < low[v]) ? low[u] : low[v];
 if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
 component_no++;
 printf("Biconnected Component %d: ", component_no);
 while (1) {
 Edge e = pop(stack);
 printf("(%d-%d) ", e.u, e.v);
 if (e.u == u && e.v == v)
 break;
 }
 printf("\n");
 }
 } else if (v != parent[u] && disc[v] < low[u]) {
 low[u] = disc[v];
 push(stack, u, v);
 }
 }
 }
}
void findBCC(int adj[MAX][MAX], int V) {
 int disc[V], low[V], parent[V];
 bool visited[V];
 Stack stack;
 stack.top = -1;
int i;
 for (i = 0; i < V; i++) {
 disc[i] = -1;
 low[i] = -1;
 parent[i] = -1;
 visited[i] = false;
 }
 for (i = 0; i < V; i++) {
 if (!visited[i]) {
 findBCCUtil(i, disc, low, parent, visited, &stack, adj, V);
 if (stack.top != -1) {
 component_no++;
 printf("Biconnected Component %d: ", component_no);
 while (stack.top != -1) {
 Edge e = pop(&stack);
 printf("(%d-%d) ", e.u, e.v);
 }
 printf("\n");
 }
 }
 }
}
int main() {
 int V, E;
 printf("Enter number of vertices and edges: ");
 scanf("%d %d", &V, &E);
 int adj[MAX][MAX] = {0};
int i;
 printf("Enter the edges (u v):\n");
 for (i = 0; i < E; i++) {
 int u, v;
 scanf("%d %d", &u, &v);
 adj[u][v] = adj[v][u] = 1;
 }
 printf("\nBiconnected Components:\n");
 findBCC(adj, V);
 return 0;
}

