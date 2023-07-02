#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
    int size;
    int *ptr_arr;
} DisjointSet;

typedef struct _PrintDisjoitSet{
    int size;
    int *ptr_arr;
} PrintDisjointSet;

void init(DisjointSet *sets, PrintDisjointSet *maze, int n);
int find(DisjointSet *sets, int x);
void union_(DisjointSet *sets, int i, int j);
void createMaze(DisjointSet *sets, PrintDisjointSet *maze, int n);
void printMaze(PrintDisjointSet *maze, int n);
void freeMaze(DisjointSet *sets, PrintDisjointSet *maze);

void init(DisjointSet *sets, PrintDisjointSet *maze, int n)
{
    sets -> size = n * n;
    sets -> ptr_arr = (int*)malloc(sizeof(int) * ((sets -> size) + 1));

    for(int i = 1; i <= sets -> size; i++)
    {
        sets -> ptr_arr[i] = 0;
    }

    maze -> size = (2 * n + 2) * n;
    maze -> ptr_arr = (int*)malloc(sizeof(int) * (maze -> size));

    for(int i = 0; i < maze -> size; i++)
    {
        maze -> ptr_arr[i] = 1;
    }

    maze -> ptr_arr[n] = 0;
    maze -> ptr_arr[(maze -> size) - n - 1] = 0;
}

int find(DisjointSet *sets, int x)
{
    if(sets -> ptr_arr[x] <= 0)
    {
        return x;
    }
    else
    {
        return (sets -> ptr_arr[x] = find(sets, sets -> ptr_arr[x]));
    }
}

void union_(DisjointSet *sets, int i, int j)
{
    int p1 = find(sets, i);
    int p2 = find(sets, j);

    if(sets -> ptr_arr[p2] < sets -> ptr_arr[p1])
    {
        sets -> ptr_arr[p1] = p2;
    }
    else 
    {
        if(sets -> ptr_arr[p2] == sets -> ptr_arr[p1])
        {
            (sets -> ptr_arr[p1])--;
        }
        sets -> ptr_arr[p2] = p1;
    }
}

void createMaze(DisjointSet *sets, PrintDisjointSet *maze, int n)
{
    srand(time(NULL));
    while(find(sets, 1) != find(sets, n * n))
    {
        int idx = rand() % (maze -> size);
        if(maze -> ptr_arr[idx] == 0 || idx < n || idx % (2 * n + 1) == 2 * n || idx % (2 * n + 1) == n || idx > (maze -> size) - n - 1)
        {
            continue;
        }
        int isHorizontal = 0;
        int i, j;
        int hor = idx % (2 * n + 1);
        for(int i = 0; i < n; i++)
        {
            if(hor == i)
                isHorizontal = 1;
        }
        if(isHorizontal)
        {
            i = (idx / (2 * n + 1) - 1) * n + idx % (2 * n + 1) + 1;
            j = i + 1;
            if(find(sets, i) != find(sets, j))
            {
                union_(sets, i, j);
                maze -> ptr_arr[idx] = 0;
            }
        }
        else
        {
            i = idx / (2 * n + 1) * n + idx % (2 * n + 1) - n;
            j = i + 1;
            if(find(sets, i) != find(sets, j))
            {
                union_(sets, i, j);
                maze -> ptr_arr[idx] = 0;
            }
        }
    }
}

void printMaze(PrintDisjointSet *maze, int n)
{
    int cnt_hor = 0;
    int cnt_ver = 0;
    for(int i = 0; i < maze -> size; i++)
    {
        int isHorizontal = 0;
        int hor = i % (2 * n + 1);
        for(int i = 0; i < n; i++)
        {
            if(hor == i)
                isHorizontal = 1;
        }
        if(isHorizontal)
        {   
            cnt_hor++;
            if(maze -> ptr_arr[i] == 1)
            {
                printf(" - ");
            }
            else
            {
                printf("   ");
            }
            if(cnt_hor % n == 0)
                printf("\n");
        }
        else
        {
            cnt_ver++;
            if(maze -> ptr_arr[i] == 1)
            {
                printf("|  ");
            }
            else
            {
                printf("   ");
            }
            if(cnt_ver % (n + 1) == 0)
                printf("\n");
        }
    }
}

void freeMaze(DisjointSet *sets, PrintDisjointSet *maze)
{
    free(sets -> ptr_arr);
    free(maze -> ptr_arr);
    free(sets);
    free(maze);
}

int main(int argc, char* argv[])
{
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSet *sets;
    PrintDisjointSet *maze;

    sets = (DisjointSet*)malloc(sizeof(DisjointSet));
    maze = (PrintDisjointSet*)malloc(sizeof(PrintDisjointSet));

    init(sets, maze, num);

    createMaze(sets, maze, num);

    printMaze(maze, num);

    freeMaze(sets, maze);

    return 0;
}