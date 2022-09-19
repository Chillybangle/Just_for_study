#include "Oneguine_functions.h"

int main ()
{
    description ();
    
    char file_name[max_size] = {0};
    get_file_name (file_name, max_size);
    
    int result = 0;
    result = launching_function (file_name);

    if (result == OK)
    {
        congratulations ();
    }
    else
    {
        failure ();
        return -1;
    }
    
    return 0;
}

int launching_function (char* file_name)
{
    FILE* input_stream = fopen (file_name, "r");
    if (input_stream == NULL)
    {
        printf ("Error: I can't open a file with this name\n");
        return FAIL;
    }
    
    size_t size = fsize (file_name);
    if (size == 0)
    {
        printf ("Error: I can't get the file size\n");
        return FAIL;
    }
    
    char* array = (char*) calloc (size + 1, sizeof (char)); // нулевой символ в конце
    
    int nread = fread (array, sizeof(char), size, input_stream); // process errors
    if (ferror (input_stream))
    {
        printf ("Error: I can't read the file\n");
        return FAIL;
    }

    size_t nstrings = nstring_counter (array);
    struct str_pointer* array_p = NULL;
    if (array_p_make (&array_p, array, nstrings) != OK)
        return FAIL;
    
    FILE* sorted_file = sorted_open();
    if (sorted_file == NULL)
        return FAIL;
    
    bubble_sort (array_p, nstrings, sizeof (struct str_pointer), &Strcmp_compar);
    file_write (sorted_file, array_p);
    
    qsort (array_p, nstrings, sizeof (struct str_pointer), &Strcmp_reversed_compar);
    file_write (sorted_file, array_p);
    
    if (original_file_write (sorted_file, array, sizeof (char), size) != OK)
        return FAIL;
    
    fclose (sorted_file);
    fclose (input_stream);
    free (array);
    free (array_p);
    
    return OK;
}
