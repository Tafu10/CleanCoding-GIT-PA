
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_lists;
} Graph;

Node *CreateNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph *CreateGraph(int vertices)
{
    int i;
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}
void AddEdge(Graph *graph, int src, int dest)
{
    Node *NewNode = CreateNode(dest);
    NewNode->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = NewNode;

    NewNode = CreateNode(src);
    NewNode->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = NewNode;
}

void PrintGraph(Graph *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        printf("Nod %d: ", i);
        Node *temp = graph->adjacency_lists[i];
        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int Empty(Node *queue)
{
    return queue == NULL;
}

void enqueue(Node **queue, int data)
{
    Node *NewNode = CreateNode(data);

    if (Empty(*queue))
    {
        *queue = NewNode;
    }
    else
    {
        Node *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = NewNode;
    }
}

int dequeue(Node **queue)
{
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void wipe_visited_list(Graph *graph) 
{
    for (int i = 0; i < graph->vertices; i++) 
    {
        graph->visited[i] = 0;
    }
}

void DFS(Graph *graph, int start)
{
    Node *adj_list = graph->adjacency_lists[start];
    graph->visited[start] = 1;
    printf("%d ", start);
    Node *temp = adj_list;
    while (temp != NULL)
    {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int start)
{
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);
    while (!Empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);
        Node *temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() 
{
    int nr_vertices;
    int nr_edges;
    int start;

    printf("Cate noduri vrei sa aiba graful: ");
    scanf("%d", &nr_vertices);
    printf("Cate muchii vrei sa aiba graful: ");
    scanf("%d", &nr_edges);

    Graph *graph = CreateGraph(nr_vertices);

    printf("Introdu muchiile (de la 0 la %d):\n", nr_vertices-1);
    for (int i = 0; i < nr_edges; i++) 
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        AddEdge(graph, src, dest);
    }

    printf("Nodul de inceput DFS: ");
    scanf("%d", &start);
    printf("DFS traversare: ");
    DFS(graph, start);
    printf("\n");

    wipe_visited_list(graph);

    printf("Nodul de inceput BFS: ");
    scanf("%d", &start);
    printf("BFS traversare: ");
    BFS(graph, start);

    return 0;
}
