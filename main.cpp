#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "C:\Users\ASUS\Downloads\CodeBlocks\MinGW\x86_64-w64-mingw32\include\sapi.h"
//#include "C:\Users\ASUS\Downloads\CodeBlocks\MinGW\x86_64-w64-mingw32\include\winapifamily.h"
//#include <festival.h>
//#include <sapi.h>

#include "tree/tree.h"
#include "io/input.h"
#include "io/output.h"
#include "../standart_functions/io/io.h"
#include "akinator/akinator.h"
//#define TX_USE_SPEAK
//#include "../TX/TXLib.h"


void print_help_info (void);


int main ()
{
    printf ("WELCOME TO AKINATOR!\n");

    const char *tree_info = "tree_info.txt";

    FILE *info_file = fopen (tree_info, "r");

    int tree_info_size = get_file_size (tree_info);
    char *buf = (char *)calloc (tree_info_size, sizeof (char));     ///buffer of "akinator" cases
    assert (buf);

    int buf_pos = 0;                                                ///free position in buffer of "akinator" cases

    Tree tree = {};
    tree_ctor (&tree);

    tree_fill (&tree, tree.root, info_file, buf, &buf_pos);

#define run_cmd(full_name, short_name, letter, number, action)  \
if (stricmp (option, full_name)  == 0 ||                        \
    stricmp (option, short_name) == 0 ||                        \
    stricmp (option, letter)     == 0 ||                        \
    stricmp (option, number)     == 0)                          \
{                                                               \
    action                                                      \
}                                                               \
else

    const int MAX_OPTION_LEN = 15;
    char option[MAX_OPTION_LEN] = "";

    for (;;)
    {
        printf ("Choose game option (\"help\" for more info):\n");

        scanf ("%s", option);

        if (stricmp (option, "help") == 0 ||
            stricmp (option, "h")    == 0)
        {
            print_help_info ();
            continue;
        }
        //run_cmd ("help", "h", "h", "h", {print_help_info (); continue;}) -- what's better??
        run_cmd ("akinator", "aki", "a", "1", {aki_play (&tree, tree.root, info_file, buf, &buf_pos, tree_info);})
        run_cmd ("definition", "def", "d", "2", {give_definition (&tree);})
        run_cmd ("compare", "comp", "c", "3", {compare (&tree);})
        run_cmd ("show", "show", "s", "4", {tree_graph (&tree);})
        run_cmd ("quit", "quit", "q", "5", {break;})
        /*else*/
        {
            printf ("ERROR: wrong command (%s)", option);
        }
    }

#undef run_cmd

    tree_dtor (&tree);

    free (buf);
    fclose (info_file);

    return 0;
}


void print_help_info (void)
{
    printf ("\"aki\"/\"akinator\"       start the game;\n"
            "\"def\"/\"definition\"     receive the definition of character;\n"
            "\"comp\"/\"compare\"       compare two characters;\n"
            "\"show\"                 receive the akinator graph;\n"
            "\"voice\"                turn on voice;\n"
            "\"quit\"                 end the game;\n"
            "\"help\"                 see this message.\n\n");
}

