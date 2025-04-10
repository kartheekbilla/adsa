

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 5
#define INF INT_MAX
typedef struct {
 int vertex;
 int weight;
} Edge;
typedef struct {
 Edge *edges;
 int size;
} Node;
Node graph[V];
void add_edge(int u, int v, int weight) {
 graph[u].edges = realloc(graph[u].edges, (graph[u].size + 1) * sizeof(Edge));
 graph[u].edges[graph[u].size].vertex = v;
 graph[u].edges[graph[u].size].weight = weight;
 graph[u].size++;
}
int min_distance(int dist[], int spt_set[]) {
 int min = INF, min_index;
 for (int v = 0; v < V; v++) {
 if (spt_set[v] == 0 && dist[v] <= min) {
 min = dist[v];
 min_index = v;
 }
 }
 return min_index;
}
void dijkstra_list(int src) {
 int dist[V];
 int spt_set[V];
 for (int i = 0; i < V; i++) {
 dist[i] = INF;
 spt_set[i] = 0;
 }
 dist[src] = 0;
 for (int count = 0; count < V - 1; count++) {
 int u = min_distance(dist, spt_set);
 spt_set[u] = 1;
 for (int i = 0; i < graph[u].size; i++) {
 int v = graph[u].edges[i].vertex;
 int weight = graph[u].edges[i].weight;
 if (!spt_set[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
 dist[v] = dist[u] + weight;
 }
 }
 }
 for (int i = 0; i < V; i++) {
 printf("Distance from source %d to vertex %d is %d\n", src, i, dist[i]);
 }
}
int main() {
 for (int i = 0; i < V; i++) {
 graph[i].size = 0;
 graph[i].edges = NULL;
 }
 add_edge(0, 1, 10);
 add_edge(0, 3, 30);
 add_edge(0, 4, 100);
 add_edge(1, 2, 50);
 add_edge(2, 3, 20);
 add_edge(2, 4, 10);
 add_edge(3, 4, 60);
 dijkstra_list(0);
 return 0;
}
