#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
    int size;
    int *key;
    int front;
    int rear;
} Queue;

Queue *CreateQueue(int X);
void Enqueue(Queue *Q, int item);
int Dequeue(Queue *Q);

Queue *CreateQueue(int X)
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));

    Q -> size = X;
    Q -> key = (int*)malloc(sizeof(int) * (Q -> size));
    Q -> front = 1;
    Q -> rear = 0;

    return Q;
}

void Enqueue(Queue *Q, int item)
{
    Q -> rear = (Q -> rear + 1) % (Q -> size);
    Q -> key[Q -> rear] = item;
}

int Dequeue(Queue *Q)
{
    int frontVal = Q -> key[Q -> front];
    Q -> front = (Q -> front + 1) % (Q -> size);
    return frontVal;
}

typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
} Graph;

Graph *CreateGraph(int X);
void InsertEdge(Graph *G, int u, int v);
void Topsort(Graph *G);

Graph *CreateGraph(int X)
{
    Graph* G = (Graph*)malloc(sizeof(Graph));

    G -> size = X;
    G -> vertex = (int*)malloc(sizeof(int) * (G -> size));
    G -> edge = (int**)malloc(sizeof(int*) * (G -> size));
    for(int i = 0; i < G -> size; i++)
    {
        G -> edge[i] = (int*)malloc(sizeof(int) * (G -> size));
    }

    return G;
}

void InsertEdge(Graph *G, int u, int v)
{
    int u_idx = 0, v_idx = 0;

    for(int i = 0; i < G -> size; i++)
    {
        if(G -> vertex[i] == u)
        {
            u_idx = i;
            break;
        }
    }

    for(int i = 0; i < G -> size; i++)
    {
        if(G -> vertex[i] == v)
        {
            v_idx = i;
            break;
        }
    }

    G -> edge[u_idx][v_idx] = 1;
}

void Topsort(Graph *G)
{
    Queue* Q;
    int V;
    int* indegree = (int*)malloc(sizeof(int) * (G -> size));

    Q = CreateQueue(G -> size);

    for(int i = 0; i < G -> size; i++)
    {
        for(int j = 0; j < G -> size; j++)
        {
            if(G -> edge[j][i] == 1)
            {
                indegree[i]++;
            }
        }
    }

    for(int i = 0; i < G -> size; i++)
    {
        if(indegree[i] == 0)
        {
            Enqueue(Q, G -> vertex[i]);
        }
    }

    while((Q -> rear + 1) % (Q -> size) != Q -> front)
    {
        int V_idx;
        V = Dequeue(Q);
        printf("%d ", V);

        for(int i = 0; i < G -> size; i++)
        {
            if(G -> vertex[i] == V)
            {
                V_idx = i;
                break;
            }
        }

        for(int i = 0; i < G -> size; i++)
        {
            if(G -> edge[V_idx][i] == 1)
            {
                G -> edge[V_idx][i] = 0;
                if(--indegree[i] == 0)
                    Enqueue(Q, G -> vertex[i]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for(int i = 0; i < X; i++)
    {
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while(fscanf(fi, "%d %d", &u, &v) != EOF)
    {
        InsertEdge(G, u, v);
    }

    Topsort(G);

    return 0;
}