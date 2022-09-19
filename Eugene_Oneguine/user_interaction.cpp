#include "Oneguine_functions.h"

void get_file_name(char* name)
{
    assert (name);
    
    printf ("Please, print name of file\n"
            "Example: Eugene_Oneguine.txt\n\t\t\t    ");
    while (fgets (name, max_size, stdin) == NULL)
        printf ("Wrong name of file or file is too long. Try again\n");
    
    while (*name != '\n')
        name++;
    *name = '\0';
}

void description ()
{
    printf ("This program sorts the poems in lexicographical and reversed lexicographical order\n"
            "\n"
            "It takes your_file.txt file and creates sorted.txt\n"
            "\n"
            "See the strength of poetry and enjoy it\n\n");
}

void congratulations ()
{
    printf ("All is OK. File is created\n");
}

void failure ()
{
    printf ("Something is not OK. I'm so sorry:(\n");
}
