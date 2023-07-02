#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct QuickSort{
    int Capacity;
    int Size;
    int *array;
};

typedef struct QuickSort* QuickSort;

QuickSort make_list(int size);
void Insert(QuickSort q, int a);
void printArray(QuickSort q);
void swap(int *a, int *b);
int middle_partition(QuickSort q, int low, int high);
int leftmost_partition(QuickSort q, int left, int right);
int rightmost_partition(QuickSort q, int left, int right);
void quicksort(QuickSort q, int left, int right, int type);

QuickSort make_list(int size)
{
    QuickSort q = (QuickSort)malloc(sizeof(struct QuickSort));

    q -> Capacity = size;
    q -> Size = 0;
    q -> array = (int*)malloc(sizeof(int) * (q -> Capacity));

    return q;
}

void Insert(QuickSort q, int a)
{
    q -> array[(q -> Size)++] = a;
}

void printArray(QuickSort q)
{
    printf("result : ");
    for(int i = 0; i < q -> Capacity; i++)
    {
        printf("%d ", q -> array[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int middle_partition(QuickSort q, int low, int high)
{
    int pivot = q -> array[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;

    for(;;)
    {
        if(j == q -> Capacity)
        {
            j = q -> Capacity - 1; 
            if(q -> array[j] != pivot)
                while(q -> array[j] > pivot)
                    j--;
        }
        else
        {
            if(q -> array[j] != pivot)
                while(q -> array[--j] > pivot);
        }

        if(i == -1)
        {
            i = 0;
            if(q -> array[i] != pivot)
                while(q -> array[i] < pivot)
                    i++;
        }
        else
        {
            if(q -> array[i] != pivot)
                while(q -> array[++i] < pivot);
        }

        if(i < j) 
            swap(&(q -> array[i]), &(q -> array[j]));
        else if(i == j)
        {
            printf("pivot value : %d\n", pivot);
            printArray(q);
            return j;
        }
    }
}


int leftmost_partition(QuickSort q, int left, int right)
{
    int pivot = q -> array[left];
    int i = left;
    int j = right + 1;
    for(;;)
    {
        while(q -> array[--j] > pivot);
        while(q -> array[++i] < pivot);
        if(i < j) 
            swap(&(q -> array[i]), &(q -> array[j]));
        else
        {
            swap(&(q -> array[j]), &(q -> array[left]));
            printf("pivot value : %d\n", pivot);
            printArray(q);
            return j;
        }
    }
}

int rightmost_partition(QuickSort q, int left, int right)
{
    int pivot = q -> array[right];
    int i = left - 1;
    int j = right;
    for(;;)
    {
        while(q -> array[--j] > pivot);
        while(q -> array[++i] < pivot);
        if(i < j) 
            swap(&(q -> array[i]), &(q -> array[j]));
        else
        {
            swap(&(q -> array[i]), &(q -> array[right]));
            printf("pivot value : %d\n", pivot);
            printArray(q);
            return i;
        }
    }
}

void quicksort(QuickSort q, int left, int right, int type)
{
    int p;
    if(left >= right)
        return;
    if(type == 0)
    {
        p = leftmost_partition(q, left, right);
        quicksort(q, left, p - 1, type);
        quicksort(q, p + 1, right, type);
    }
    else if(type == 1)
    {
        p = rightmost_partition(q, left, right);
        quicksort(q, left, p - 1, type);
        quicksort(q, p + 1, right, type);
    }
    else if(type == 2)
    {
        p = middle_partition(q, left, right);
        quicksort(q, left, p - 1, type);
        quicksort(q, p + 1, right, type);
    }
}

void main(int argc, char* argv[])
{
    char type_s[10];
    int list_size, key, type_i;
    QuickSort q;
    FILE *fi = fopen(argv[1], "r");

    fscanf(fi, "%s", &type_s);
    if(!(strcmp(type_s, "leftmost"))) type_i = 0;
    else if(!(strcmp(type_s, "rightmost"))) type_i = 1;
    else if(!(strcmp(type_s, "middle"))) type_i = 2;

    fscanf(fi, "%d", &list_size);
    q = make_list(list_size);
    for(int i = 0; i < list_size; i++)
    {
        fscanf(fi, "%d", &key);
        Insert(q, key);
    }

    quicksort(q, 0, list_size - 1, type_i);

    free(q -> array);
    free(q);
}