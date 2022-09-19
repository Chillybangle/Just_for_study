#include "Oneguine_functions.h"

void get_file_name(char* name, const int max_size)
{
    printf ("Please, print name of file\n");
    printf ("Example: Eugene_Oneguine.txt\n\t\t\t    ");
    while (fgets (name, max_size, stdin) == NULL)
        printf ("Wrong name of file. Try again\n");
}

void description ()
{
    printf ("This program sorts the poems ");
    printf ("in lexicographical and reversed lexicographical order\n\n");
    
    printf ("It takes your_file.txt file and ");
    printf ("creates sorted.txt\n");
    
    printf ("\nSee the strength of poetry and enjoy it\n\n");
}

void congratulations ()
{
    printf ("All is OK. File was created\n");
}

void failure ()
{
    printf ("Something is not OK. I'm so sorry:(\n");
}
