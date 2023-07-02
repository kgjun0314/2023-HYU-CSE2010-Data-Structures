#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    char *name;
    int student_id;
    char *major;
}student;

int main(int argc, char** args)
{
    char *input_path, *output_path;
    FILE *fi, *fo;

    int num;
    int i;

    student* students;

    input_path = args[1];
    output_path = args[2];

    fi = fopen(input_path, "r");
    fo = fopen(output_path, "w");

    fscanf(fi, "%d", &num);

    students = (student*) malloc(num * sizeof(student));

    for (i = 0; i < num; i++) 
    {
        students[i].name = (char*) malloc(31 * sizeof(char));
        students[i].major = (char*) malloc(31 * sizeof(char));
        fscanf(fi, "%s %d %s", students[i].name, &students[i].student_id, students[i].major);
    }

    for (i = 0; i < num; i++) 
    {
        fprintf(fo, "%s\t%d\t%s\n", students[i].name, students[i].student_id, students[i].major);
    }

    for (i = 0; i < num; i++) 
    {
        free(students[i].name);
        free(students[i].major);
    }
    free(students);

    fclose(fi);
    fclose(fo);

    return 0;
}