#include "Oneguine_functions.h"

int file_write (char** array)
{
    char name[] = "sorted.txt";
    
    FILE* sorted_file = fopen (name, "w");
    if (sorted_file == NULL)
    {
        printf ("Error: I can't create sorted file\n");
        return FAIL;
    }
    
    for (long int i = 0; array[i] != NULL; i++)
    {
        if (*array[i] != 'r' && *array[i] != '\n')
            fputs_my (array[i], sorted_file);
    }
    fclose (sorted_file);
    
    return OK;
}
