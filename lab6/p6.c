#include<stdio.h>
#include<stdlib.h>

struct TreeStruct{
    int size;
    int numOfNode;
    int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void PrintPreorder(Tree tree, int index);
void PrintInorder(Tree tree, int index);
void PrintPostorder(Tree tree, int index);
void DeleteTree(Tree tree);

Tree CreateTree(int size)
{
    Tree tree = (Tree)malloc(sizeof(struct TreeStruct));

    tree -> size = size;
    tree -> numOfNode = 0;
    tree -> element = (int*)malloc(sizeof(int) * (tree -> size));

    return tree;
}

void Insert(Tree tree, int value)
{
    if(tree -> numOfNode == tree -> size)
    {
        printf("Error! Tree is full.\n");
        return;
    }
    else
        tree -> element[++(tree -> numOfNode)] = value;
}

void PrintTree(Tree tree)
{
    printf("Preorder: ");
    PrintPreorder(tree, 1);
    printf("\n");
    printf("Inorder: ");
    PrintInorder(tree, 1);
    printf("\n");
    printf("Postorder: ");
    PrintPostorder(tree, 1);
    printf("\n");
}

void PrintPreorder(Tree tree, int index)
{
    if(index > tree -> numOfNode)
        return;
    printf("%d ", tree -> element[index]);
    PrintPreorder(tree, 2 * index);
    PrintPreorder(tree, 2 * index + 1);
}

void PrintInorder(Tree tree, int index)
{
    if(index > tree -> numOfNode)
        return;
    PrintInorder(tree, 2 * index);
    printf("%d ", tree -> element[index]);
    PrintInorder(tree, 2 * index + 1);
}

void PrintPostorder(Tree tree, int index)
{
    if(index > tree -> numOfNode)
        return;
    PrintPostorder(tree, 2 * index);
    PrintPostorder(tree, 2 * index + 1);
    printf("%d ", tree -> element[index]);
}

void DeleteTree(Tree tree)
{
    free(tree -> element);
    free(tree);
}

void main(int argc, char* argv[])
{
    FILE *fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);

    while(fscanf(fi, "%d", &tmpNum) == 1)
    {
        Insert(tree, tmpNum);
    }
    PrintTree(tree);
    DeleteTree(tree);
}