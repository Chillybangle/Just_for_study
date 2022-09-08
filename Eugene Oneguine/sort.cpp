#include "Oneguine_functions.h"
#include "string_functions.h"

static int poem_into_arr (char** array, long unsigned int n, FILE* stream);
static void free_array (char** array, unsigned long int nstrings);
static int file_write (char** array, long unsigned int nstrings);

int poem_sort (FILE* stream)
{
    long unsigned int nstrings = 8052;
    char** array = (char**) calloc (nstrings, sizeof (char*)); // нужно придумать как эффективно узнать количество строк
    if (array == NULL)
    {
        printf ("Fail: array was not created\n");
        return FAIL;
    }
    
    if (poem_into_arr (array, nstrings, stream) == FAIL)
    {
        printf ("Fail: poem was not placed in the array\n");
        return FAIL;
    }
    //Переделать под универсальный подсчет символов (сначала считать файл, по мере считывания установить указатели)
    //Управляющая функция (сортировка только сортирует)
    //Имя должно быть любое (другой файл изи)
    //Сортировка в рифму (сортирующиеся строчки рядом)
    //Строки пустые убрать
    char* str_pointer = NULL;
    for (unsigned long int i = 0; i < nstrings; i++)
    {
        for (unsigned long int j = 0; j < (nstrings - 1 - i); j++)
        {
            if (strcmp(array[j], array[j + 1]) > 0)
            {
                str_pointer = array[j];
                array[j] = array[j + 1];
                array[j + 1] = str_pointer;
            }
        }
    }
    
    if (file_write (array, nstrings) == FAIL)
        return FAIL;
    
    free_array (array, nstrings);
    
    return 0;
}

static int poem_into_arr (char** array, long unsigned int nstrings, FILE* stream)
{
    size_t current_nsymb = 0;
    for (long unsigned int i = 0; i < nstrings; i++)
    {
        if (getline (&array[i], &current_nsymb, stream) == FAIL)
            return FAIL;
        current_nsymb = 0;
    }
    
    return 0;
}

static void free_array (char** array, unsigned long int nstrings)
{
    for (unsigned long int i = 0; i < nstrings; i++)
    {
        free (array[i]);
    }
    free (array);
}

static int file_write (char** array, long unsigned int nstrings)
{
    FILE* sorted_file = fopen ("Eugene_Oneguine_sorted.txt", "w");
    if (sorted_file == NULL)
    {
        printf ("Fail: sorted file is not created\n");
        return FAIL;
    }
    
    for (unsigned long int i = 0; i < nstrings; i++)
    {
        fputs (array[i], sorted_file);
    }
    fclose (sorted_file);
    
    return 0;
}
