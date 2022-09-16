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
    
    int size = fsize (file_name);
    //printf ("File size is %d b\n", size);
    
    char* array = (char*) calloc (size + 1, sizeof (char)); // нулевой символ в конце
    char** array_p = NULL;
    
    int nread = fread (array, sizeof(char), size, stream);
    //printf ("Я прочитал %d символов\n", nread);
    
    //printf ("Содержание файла:\n\n\n%s\n\n", array);
    
    //printf ("Количество строк в файле: %d\n", nstring_counter (array));
    
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
    if (poem_sort (nstrings, array_p) != OK)
        return FAIL;
    
    if (file_write (array_p) != OK)
        return FAIL;
    
    fclose (stream);
    free (array);
    free (array_p);
    
    return OK;
}
