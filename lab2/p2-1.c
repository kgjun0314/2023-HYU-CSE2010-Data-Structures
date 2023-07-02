#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("enter %s names: \n", argv[1]);
    int n = atoi(argv[1]);

    char** names = (char**) malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++)
    {
        names[i] = (char*) malloc(31 * sizeof(char));
    }

    for(int i = 0; i < n; i++)
    {
        char name[31];
        scanf("%s", name);
        strcpy(names[i], name);
    }

    printf("the names you entered:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s\n", names[i]);
    } 

    for(int i = 0; i < n; i++)
    {
        free(names[i]);
    }   
    free(names);

    return 0;
}