#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree_struct.h"
#include "tree/tree.h"
#include "io/input.h"
#include "../standart_functions/io/io.h"
#include "akinator/akinator.h"

static const char *tree_info = "tree_info.txt";

void print_help_info (void);

int main ()
{
    printf ("choose game option (help for more info)\n");

    char option[10] = {};
    scanf ("%s", option);

    if (stricmp (option, "help") == 0 ||
        *option == 'h' ||
        *option == 'H')
    {
        print_help_info ();

        return 0;
    }

    FILE *info_file = fopen (tree_info, "r");

    int tree_info_size = get_file_size (tree_info);
    char *buf = (char *)calloc (tree_info_size, sizeof (char));
    assert (buf);

    Tree tree = {};
    tree_ctor (&tree);

    tree_fill (&tree, tree.root, info_file, buf);

    if (stricmp (option, "aki") == 0 ||
        stricmp (option, "akinator") == 0 ||
        *option == 'a' ||
        *option == 'A' ||
        *option == '1')
    {
        aki_play (tree.root);
    }
    else if (stricmp (option, "def") == 0 ||
             stricmp (option, "definition") == 0 ||
             *option == 'd' ||
             *option == 'D' ||
             *option == '2')
    {
        ;
    }
    else if (stricmp (option, "comp") == 0 ||
             stricmp (option, "compare") == 0||
             *option == 'c' ||
             *option == 'C' ||
             *option == '3')
    {
        ;
    }
    else if (stricmp (option, "show") == 0 ||
             *option == 's' ||
             *option == 'S' ||
             *option == '4')
    {
        tree_graph (&tree, info_file);
    }
    else if (stricmp (option, "voice") == 0 ||
             *option == 'v' ||
             *option == 'V' ||
             *option == '5')
    {
        ;
    }
    else
    {
        printf ("ERROR: wrong command (%s)", option);
    }

    tree_dtor (&tree);

    free (buf);
    fclose (info_file);
}

void print_help_info (void)
{
    printf ("1 or akinator to start the game\n"
            "2 or define to receive the definition of character or give it to the new one\n"
            "3 or compare to compare two characters"
            "4 or show to see the akinator graph"
            "5 or voice to turn voice");
}

