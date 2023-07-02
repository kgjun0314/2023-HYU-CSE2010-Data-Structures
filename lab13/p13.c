#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node{
    int vertex;
    int dist;
    int prev;
} Node;

typedef struct Graph{
    int size;
    Node* nodes;
    int** matrix;
} Graph;

Graph* createGraph(int X);
Graph* findShortestPath(Graph* G, int s);
void printShortestPath(Graph* G);

typedef struct Heap{
    int capacity;
    int size;
    Node* elements;
} Heap;

Heap* createMinHeap(int X);
void insert(Heap* H, Node N);
Node deleteMin(Heap* H);
void decreaseKey(Heap* H, Node N);

Graph* createGraph(int X)
{
    Graph* G = (Graph*)malloc(sizeof(Graph));

    G -> size = X;
    G -> nodes = (Node*)malloc((X + 1) * sizeof(Node));
    G -> matrix = (int**)malloc((X + 1) * sizeof(int*));

    for (int i = 1; i <= X; i++) 
    {
        G -> nodes[i].vertex = i;
        G -> nodes[i].dist = INF;
        G -> nodes[i].prev = 0;
        G -> matrix[i] = (int*)malloc((X + 1) * sizeof(int));
        for (int j = 1; j <= X; j++) {
            G -> matrix[i][j] = INF;
        }
    }

    return G;
}

Graph* findShortestPath(Graph* G, int s)
{
    Heap* H = createMinHeap(G -> size);

    G -> nodes[s].dist = 0;

    for(int v = 1; v <= G -> size; v++)
    {
        if(s == v)
            continue;
        if(G -> matrix[s][v] != INF)
        {
            G -> nodes[v].dist = G -> matrix[s][v];
            G -> nodes[v].prev = G -> nodes[s].vertex;
            insert(H, G -> nodes[v]);
        }       
    }

    while(H -> size != 0)
    {
        Node u = deleteMin(H);

        for(int v = 1; v <= G -> size; v++)
        {
            if(u.vertex == v)
                continue;
            if(G -> matrix[u.vertex][v] != INF)
            {
                if(G -> nodes[u.vertex].dist + G -> matrix[u.vertex][v] < G -> nodes[v].dist)
                {
                    G -> nodes[v].dist = G -> nodes[u.vertex].dist + G -> matrix[u.vertex][v];
                    G -> nodes[v].prev = u.vertex;
                    insert(H, G -> nodes[v]);
                }
            }
        }   
    }

    return G;
}

void printShortestPath(Graph* G)
{
    for (int i = 2; i <= G->size; i++) 
    {
        if (G -> nodes[i].dist == INF)
            printf("%d can not be reached.\n", i);

        else 
        {
            printf("%d", i);
            int prev = G -> nodes[i].prev;
            while (prev != 0) 
            {
                printf("<-%d", prev);
                prev = G->nodes[prev].prev;
            }
            printf(" cost: %d\n", G -> nodes[i].dist);
        }
    }
}

Heap* createMinHeap(int X)
{
    Heap* H = (Heap*)malloc(sizeof(Heap));
    H -> capacity = X;
    H -> size = 0;
    H -> elements = (Node*)malloc((X + 1) * sizeof(Node));
    return H;
}

void insert(Heap* H, Node N)
{
    int i;

    for(i = 1; i <= H -> size; i++)
    {
        if(H -> elements[i].vertex && H -> elements[i].vertex == N.vertex)
        {
            decreaseKey(H, N);
            return;
        }
    }

    for(i = ++(H -> size); H->elements[i / 2].dist > N.dist; i /= 2)
        H -> elements[i] = H -> elements[i / 2];
    
    H -> elements[i] = N;
}

Node deleteMin(Heap* H)
{
    int i, Child;
    Node MinElement, LastElement;

    MinElement = H -> elements[1];
    LastElement = H -> elements[(H -> size)--];

    for(i = 1; i * 2 <= H -> size; i = Child)
    {
        Child = i * 2;
        if(Child != H -> size && H -> elements[Child + 1].dist < H -> elements[Child].dist)
            Child++;
        if(LastElement.dist > H -> elements[Child].dist)
            H -> elements[i] = H -> elements[Child];
        else
            break;
    }
    H -> elements[i] = LastElement;
    return MinElement;
}

void decreaseKey(Heap* H, Node N)
{
    int i;
    for(i = 1; i <= H -> size; i++) 
    {
        if (H -> elements[i].vertex == N.vertex) 
        {
            H -> elements[i].dist = N.dist;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    FILE *fi = fopen(argv[1], "r");
    int size;

    fscanf(fi, "%d", &size);

    Graph* G = createGraph(size);

    int node_s, node_d, weight;
    while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF){
        G -> matrix[node_s][node_d] = weight;
    }

    G = findShortestPath(G, 1);

    printShortestPath(G);

    return 0;
}