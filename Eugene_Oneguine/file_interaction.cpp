#include "Oneguine_functions.h"

int file_write (struct str_pointer* array_p)
{
    static int nwrites = 0; //< number of entries in the file sorted.txt
    
    FILE* sorted_file = NULL;
    if (nwrites == 0)
        sorted_file = fopen (name_of_sorted_file, "w");
    else
        sorted_file = fopen (name_of_sorted_file, "a");
    
    if (sorted_file == NULL)
    {
        printf ("Error: I can't create sorted file\n");
        return FAIL;
    }
    
    for (long int i = 0; array_p[i].p != NULL; i++)
    {
        if (*(array_p[i].p) != '\r' && *(array_p[i].p) != '\n')
            fputs_my (array_p[i].p, sorted_file);
    }
    fclose (sorted_file);
    nwrites++;
    
    return OK;
}

int original_file_write (char* array, size_t size_of_elem, size_t nmemb)
{
    FILE* stream = fopen (name_of_sorted_file, "a");
    if (stream == NULL)
    {
        printf ("Error: I can't open sorted file\n");
        return FAIL;
    }
    
    size_t nwritten = 0;
    nwritten = fwrite (array, size_of_elem, nmemb, stream);
    if (nwritten != nmemb)
    {
        printf ("Error: The number of recorded elements does not match the transmitted on\n");
        return FAIL;
    }
    
    fclose (stream);
    
    return OK;
}
