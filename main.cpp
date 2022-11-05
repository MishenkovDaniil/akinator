#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "akinator/akinator.h"
#include "io/input.h"
#include "../standart_functions/io/io.h"

static const char *tree_info = "tree_info.txt";

int main ()
{
    FILE *info_file = fopen (tree_info, "r");

    int tree_info_size = get_file_size (tree_info);
    char *buf = (char *)calloc (tree_info_size, sizeof (char));
    assert (buf);

    Tree tree = {};
    tree_ctor (&tree);

    tree_fill (&tree, tree.root, info_file, buf);

    printf ("%s\n", tree.root->node_case);

    tree_dtor (&tree);

    free (buf);
    fclose (info_file);
}
