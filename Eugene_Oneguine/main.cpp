#include "Oneguine_functions.h"
#define DEBU

int main ()
{
#ifndef DEBUG
    description ();
    
    char file_name[max_size] = {0};
    get_file_name (file_name, max_size);
    
    int result = 0;
    result = launching_function (file_name);

    if (result == OK)
        congratulations ();
    else
        failure ();
    
    return 0;
#endif
    
#ifdef DEBUG
    
#endif
}

int launching_function (char* file_name)
{
    FILE* stream = fopen (file_name, "r");
    if (stream == NULL)
    {
        printf ("Error: I can't open a file with this name\n");
        return FAIL;
    }
    
    size_t size = fsize (file_name);
    //printf ("File size is %d b\n", size);
    
    char* array = (char*) calloc (size + 1, sizeof (char)); // нулевой символ в конце
    
    int nread = fread (array, sizeof(char), size, stream); // process errors
    //printf ("Я прочитал %d символов\n", nread);
    
    //printf ("Содержание файла:\n\n\n%s\n\n", array);
    
    //printf ("Количество строк в файле: %d\n", nstring_counter (array));
    
    struct str_pointer* array_p = NULL;
    if (array_p_make (&array_p, array) != OK)
        return FAIL;
    
    //printf ("Я тут\n");
    //printf ("Печатаю строку из массива указателей:\n%s\n", array_p[7]);
    //printf ("Я здесь\n");
    
    //char s1[] = "1\n";
    //char s2[] = "2\n";
    //int diff = strcmp_my (s1, s2);
    //printf ("Result of strcmp: %d\n", diff);
    
    size_t nstrings = nstring_counter (array);
    
    bubble_sort (array_p, nstrings, sizeof (struct str_pointer), &Strcmp_compar);
    if (file_write (array_p) != OK)
        return FAIL;
    
    qsort (array_p, nstrings, sizeof (struct str_pointer), &Strcmp_reversed_compar);
    if (file_write (array_p) != OK)
        return FAIL;
    
    if (original_file_write (array, sizeof (char), size) != OK)
        return FAIL;
    
    fclose (stream); // file_stream? input_stream? output_stream?
    free (array);
    free (array_p);
    
    return OK;
}
