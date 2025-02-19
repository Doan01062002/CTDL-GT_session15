#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
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

void dfs(Graph* graph, int vertex) {
    graph->visited[vertex] = 1;

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (graph->visited[adjVertex] == 0) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }
}

int isConnected(Graph* graph) {
    dfs(graph, 0);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int vertices, edges;
    printf("So dinh: ");
    scanf("%d", &vertices);
    printf("So canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Nhap cac canh (u, v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (isConnected(graph)) {
        printf("Do thi lien thong\n");
    } else {
        printf("Do thi khong lien thong\n");
    }

    return 0;
}

