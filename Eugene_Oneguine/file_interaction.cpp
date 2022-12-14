#include "Oneguine_functions.h"

void file_write (FILE* sorted_file, struct str_pointer* array_p)
{
    assert (sorted_file);
    assert (array_p);
    
    for (long int i = 0; array_p[i].p != NULL; i++)
    {
            fputs_my (array_p[i].p, sorted_file);
    }
}

FILE* sorted_open ()
{
    FILE* sorted_file = fopen (name_of_sorted_file, "w");
    if (sorted_file == NULL)
    {
        printf ("Error: I can't create sorted file\n");
        return NULL;
    }
    
    return sorted_file;
}

int original_file_write (FILE* sorted_file, char* array, size_t size_of_elem, size_t nmemb)
{
    assert (sorted_file);
    assert (array);
    
    size_t nwritten = 0;
    nwritten = fwrite (array, size_of_elem, nmemb, sorted_file);
    if (nwritten != nmemb)
    {
        printf ("Error: The number of recorded elements does not match the transmitted on\n");
        return FAIL;
    }
    
    return OK;
}
