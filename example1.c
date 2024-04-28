
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adjacency_list;
} Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} Stack;

Node *CreateNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void AddEdge(Graph *graph, int src, int dest)
{
    Node *newNode = CreateNode(dest);
    newNode->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = newNode;
    newNode = CreateNode(src);
    newNode->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = newNode;
}

Graph *CreateGraph(int vertices)
{
    int i;
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_list = malloc(sizeof(Node *) * vertices);
    graph->visited = malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *CreateStack(int capacity)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int pushed_element, Stack *stack)
{
    stack->top++;
    stack->array[stack->top] = pushed_element;
}

void DFS(Graph *graph, Stack *stack, int vertex) 
{
    Node *adj_list = graph->adjacency_list[vertex];
    Node *aux = adj_list;
    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    push(vertex, stack);
    while (aux != NULL) 
    {
        int connected_vertex = aux->data;
        if (graph->visited[connected_vertex] == 0)
            DFS(graph, stack, connected_vertex);
        aux = aux->next;
    }
}

void InsertEdges(Graph *graph, int edge_nr, int nr_vertices)
{
    int src, dest, i;
    printf("Adauga %d muchii (de la 0 la %d)\n", edge_nr, nr_vertices-1);
    for (i = 0; i < edge_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        AddEdge(graph, src, dest);
    }
}

void Path(Graph *graph, int nr_vertices, Stack *stack) 
{
    int ok = 1;
    DFS(graph, stack, 0);
    for (int i = 0; i < nr_vertices; i++) 
    {
        if (graph->visited[i] == 0) 
        {
            ok = 0;
            break;
        }
    }
    printf("\nPoate fi strabatut: %s\n", ok ? "Da" : "Nu");
}

int main()
{

    int nr_vertices, edge_nr;

    printf("Cate noduri are graful:");
    scanf("%d", &nr_vertices);

    printf("Cate muchii are graful:");
    scanf("%d", &edge_nr);

    Graph *graph = CreateGraph(&nr_vertices);
    Stack *stack = CreateStack(2 * nr_vertices);

    InsertEdges(graph, edge_nr, nr_vertices);
    Path(graph, nr_vertices, stack);

    return 0;
}
