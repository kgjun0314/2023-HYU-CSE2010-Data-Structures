#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
    ElementType element;
    Position next;
};

List MakeEmptyList();
int isLast(Position, List l);
void Delete(ElementType x, List l);
Position FindPrevious(ElementType x, List l);
Position Find(ElementType x, List l);
void Insert(ElementType x, Position p, List l);
void DeleteList(List l);
void PrintList(List l);

List MakeEmptyList()
{
    List l = (List)malloc(sizeof(struct Node));
    l -> element = -999;
    l -> next = NULL;
    return l;
}

int isLast(Position p, List l)
{
    Position current = l;
    while(current -> next != NULL)
        current = current -> next;
    return p == current;
}

Position FindPrevious(ElementType x, List l)
{
    Position p;
    p = l;
    while(p -> next != NULL && p -> next -> element != x)
    {
        p = p -> next;
    }
    return p;
}

Position Find(ElementType x, List l)
{
    if(x == -1)
    {
        return l;
    }
    else
    {
        Position p;
        p = l -> next;
        while(p != NULL && p -> element != x)
        {
            p = p -> next;
        }
        return p;
    }
}

void Insert(ElementType x, Position p, List l)
{
    if(p == NULL)
    {
        printf("Insertion(%d) Failed: cannot find the location to be inserted.\n", x);
    }
    else
    {
        Position tmp;
        tmp = (Position)malloc(sizeof(struct Node));
        
        tmp -> element = x;
        tmp -> next = p -> next;
        p -> next = tmp;
    }
}

void Delete(ElementType x, List l)
{
    Position p, tmp;
    p = FindPrevious(x, l);
    if(p -> next == NULL)
    {
        printf("Deletion failed: element %d is not in the list\n", x);
    }
    else if(!isLast(p, l))
    {
        tmp = p -> next;
        p -> next = tmp -> next;
        free(tmp);
    }
}

void PrintList(List l)
{
    PtrToNode tmp = NULL;
    tmp = l -> next;
    if(tmp == NULL)
    {
        printf("list is empty!\n");
        return;
    }
    while(tmp != NULL)
    {
        printf("key: %d\t", tmp -> element);
        tmp = tmp -> next;
    }
    printf("\n");
}

void DeleteList(List l)
{
    Position p = NULL, tmp = NULL;
    p = l -> next;
    l -> next = NULL;
    while(p != NULL)
    {
        tmp = p -> next;
        free(p);
        p = tmp;
    }
}

int main(int argc, char* argv[])
{
    char command;
    char buffer;
    int key1, key2;
    FILE *input, *output;
    Position header = NULL, tmp = NULL;

    if(argc <= 1)
    {
        printf("Please enter an input file.\n");
        return 0;
    }
    else
        input = fopen(argv[1], "r");
    
    header = MakeEmptyList();
    while(1)
    {
        command = fgetc(input);
        if(feof(input)) break;

        switch(command)
        {
            case 'i':
                fscanf(input, "%d %d", &key1, &key2);
                buffer = fgetc(input);
                tmp = Find(key2, header);
                Insert(key1, tmp, header);
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                buffer = fgetc(input);
                Delete(key1, header);
                break;
            case 'f':
                fscanf(input, "%d", &key1);
                buffer = fgetc(input);
                tmp = FindPrevious(key1, header);
                if(isLast(tmp, header))
                    printf("Could not find %d in the list.\n", key1);
                else if(tmp -> element > 0)
                    printf("Key of the previous node of %d id %d.\n", key1, tmp -> element);
                else
                    printf("key of the previoud node of %d is header.\n", key1);
                break;
            case 'p':
                PrintList(header);
                buffer = fgetc(input);
                break;
            default:
                printf("Invalid command line\n");
                buffer = fgetc(input);
        }
    }

    DeleteList(header);
    fclose(input);

    return 0;
}
