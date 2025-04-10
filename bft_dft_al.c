

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node {
 int vertex;
 struct Node* next;
} Node;
typedef struct Graph {
 int numVertices;
 Node* adjLists[MAX];
 int visited[MAX];
} Graph;
typedef struct Queue {
 int items[MAX];
 int front, rear;
} Queue;
typedef struct Stack {
 int items[MAX];
 int top;
} Stack;
Node* createNode(int v) {
 Node* newNode = (Node*)malloc(sizeof(Node));
 newNode->vertex = v;
 newNode->next = NULL;
 return newNode;
}
Graph* createGraph(int vertices) {
int i;
 Graph* graph = (Graph*)malloc(sizeof(Graph));
 graph->numVertices = vertices;
 for (i = 0; i < vertices; i++) {
 graph->adjLists[i] = NULL;
 graph->visited[i] = 0;
 }
 return graph;
}
void addEdge(Graph* graph, int src, int dest) {
 Node* newNode = createNode(dest);
 newNode->next = graph->adjLists[src];
 graph->adjLists[src] = newNode;
 newNode = createNode(src);
 newNode->next = graph->adjLists[dest];
 graph->adjLists[dest] = newNode;
}
Queue* createQueue() {
 Queue* q = (Queue*)malloc(sizeof(Queue));
 q->front = 0;
 q->rear = 0;
 return q;
}
int isQueueEmpty(Queue* q) {
 return q->front == q->rear;
}
void enqueue(Queue* q, int value) {
 if (q->rear == MAX) {
 printf("Queue is full\n");
 return;
 }
 q->items[q->rear++] = value;
}
int dequeue(Queue* q) {
 if (isQueueEmpty(q)) {
 printf("Queue is empty\n");
 return -1;
 }
 return q->items[q->front++];
}
Stack* createStack() {
 Stack* s = (Stack*)malloc(sizeof(Stack));
 s->top = -1;
 return s;
}
int isStackEmpty(Stack* s) {
 return s->top == -1;
}
void push(Stack* s, int value) {
 if (s->top == MAX - 1) {
 printf("Stack is full\n");
 return;
 }
 s->items[++s->top] = value;
}
int pop(Stack* s) {
 if (isStackEmpty(s)) {
 printf("Stack is empty\n");
 return -1;
 }
 return s->items[s->top--];
}
void bft_adjacency_list(Graph* graph, int start) {
 Queue* q = createQueue();
 graph->visited[start] = 1;
 enqueue(q, start);
 printf("BFT using Adjacency List: ");
 while (!isQueueEmpty(q)) {
 int node = dequeue(q);
 printf("%d ", node);
 Node* temp = graph->adjLists[node];
 while (temp) {
 int adjVertex = temp->vertex;
 if (!graph->visited[adjVertex]) {
 graph->visited[adjVertex] = 1;
 enqueue(q, adjVertex);
 }
 temp = temp->next;
 }
 }
 printf("\n");
}
void dft_adjacency_list(Graph* graph, int start) {
 Stack* s = createStack();
 push(s, start);
 printf("DFT using Adjacency List: ");
 while (!isStackEmpty(s)) {
 int node = pop(s);
 if (!graph->visited[node]) {
 printf("%d ", node);
 graph->visited[node] = 1;
 Node* temp = graph->adjLists[node];
 while (temp) {
 int adjVertex = temp->vertex;
 if (!graph->visited[adjVertex]) {
 push(s, adjVertex);
 }
 temp = temp->next;
 }
 }
 }
 printf("\n");
}
int main() {
int i;
 Graph* graph = createGraph(4);
 addEdge(graph, 0, 1);
 addEdge(graph, 0, 2);
 addEdge(graph, 1, 3);
 addEdge(graph, 2, 3);
 bft_adjacency_list(graph, 0);
 for (i = 0; i < graph->numVertices; i++) {
 graph->visited[i] = 0;
 }
 dft_adjacency_list(graph, 0);
 return 0;
}