#include <stdio.h>

int main ()
{
    FILE *file = fopen ("tree_info.txt", "r");

    char cmd[100] = {};

    int temp = 0;

    fscanf (file, "%s%n", cmd, &temp);
    printf ("%d", temp);

    fscanf (file, "%s%n", cmd+1, &temp);
    printf ("%d", temp);

    printf ("[%s]", cmd);


    fclose (file);
}

