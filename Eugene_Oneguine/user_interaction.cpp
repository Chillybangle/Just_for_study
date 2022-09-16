#include "Oneguine_functions.h"

void get_file_name(char* name, const int max_size)
{
    printf ("Please, print name of file\n");
    printf ("Example: Eugene_Oneguine.txt\n");
    while (fgets (name, max_size, stdin) == NULL)
        printf ("Wrong name of file. Try again\n");
}

void description ()
{
    printf ("This program sorts the poem Eugene Oneguine ");
    printf ("in lexicographical order\n\n");
    
    printf ("It takes Eugene_Oneguine.txt file and ");
    printf ("creates sorted.txt\n");
    
    printf ("\n\nSee the strength of Russian poetry and enjoy it\n\n");
}

void congratulations ()
{
    printf ("All is OK. File was created\n");
}

void failure ()
{
    printf ("Something is not OK. I'm so sorry:(\n");
}
