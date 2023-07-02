#include <stdio.h>
#include <stdlib.h>

struct MergeSort{
    int Capacity;
    int Size;
    int *array;
    int *Tmparray; 
};

typedef struct MergeSort* MergeSort;

MergeSort make_list(int size);
void Insert(MergeSort m, int a);
void printArray(MergeSort A, int l, int r);
void RmergeSort(MergeSort A, int l, int r);
void ImergeSort(MergeSort A, int n);
void merge(MergeSort A, int l, int m, int r);

MergeSort make_list(int size)
{
    MergeSort m = (MergeSort)malloc(sizeof(struct MergeSort));

    m -> Capacity = size;
    m -> Size = 0;
    m -> array = (int*)malloc(sizeof(int) * (m -> Capacity));
    m -> Tmparray = (int*)malloc(sizeof(int) * (m -> Capacity));

    return m;
}

void Insert(MergeSort m, int a)
{
    m -> array[(m -> Size)++] = a;
}

void printArray(MergeSort A, int l, int r)
{
    for(int i = l; i <= r; i++)
    {
        printf("%d ", A -> array[i]);
    }
    printf("\n");
}

void RmergeSort(MergeSort A, int l, int r)
{
    int Center;
    if(l < r)
    {
        Center = (l + r) / 2;
        RmergeSort(A, l, Center);
        RmergeSort(A, Center + 1, r);
        merge(A, l, Center + 1, r);
    }
}

void ImergeSort(MergeSort A, int n)
{
    int i, l, Center, r;

    for (i = 1; i <= n - 1; i = 2 * i)
    {
        for (l = 0; l < n - 1; l += 2 * i) 
        {
            Center = l + i - 1;

            if(l + 2 * i - 1 < n - 1)
                r = (l + 2 * i - 1);
            else
                r = n - 1;

            merge(A, l, Center + 1, r);
        }
    }
}

void merge(MergeSort A, int l, int m, int r)
{
    int i, LeftEnd, NumElements, TmpPos;
    LeftEnd = m - 1;
    TmpPos = l;
    NumElements = r - l + 1;
    int templ = l;

    while(l <= LeftEnd && m <= r)
    {
        if(A -> array[l] <= A -> array[m])
            A -> Tmparray[TmpPos++] = A -> array[l++];
        else
            A -> Tmparray[TmpPos++] = A -> array[m++];
    }

    while(l <= LeftEnd)
        A -> Tmparray[TmpPos++] = A -> array[l++];

    while(m <= r)
        A -> Tmparray[TmpPos++] = A -> array[m++];

    for(i = 0; i < NumElements; i++, templ++)
    {
        A -> array[templ] = A -> Tmparray[templ];
        printf("%d ", A -> array[templ]);
    }
    printf("\n");
}

void main(int argc, char* argv[])
{
    int size, key;
    int *iter_tmp, *rec_tmp;
    FILE *fi = fopen(argv[1], "r");
    MergeSort iter_m, rec_m;

    fscanf(fi, "%d", &size);

    iter_m = make_list(size);
    rec_m = make_list(size);

    for(int i = 0; i < size; i++)
    {
        fscanf(fi, "%d", &key);
        Insert(iter_m, key);
        Insert(rec_m, key);
    }

    printf("input : \n");
    printArray(iter_m, 0, iter_m -> Size - 1);
    printf("\n");

    printf("iterative : \n");
    ImergeSort(iter_m, iter_m -> Size);
    printf("\n");

    printf("recursive : \n");
    RmergeSort(rec_m, 0, rec_m -> Size - 1);
    printf("\n");
}