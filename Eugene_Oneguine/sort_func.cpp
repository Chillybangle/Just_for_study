#include "Oneguine_functions.h"

int poem_sort (long int nstrings, char** array_p)
{
    char* str_pointer = NULL;
    for (long int i = 0; i < nstrings; i++)
    {
        for (long int j = 0; j < (nstrings - 1 - i); j++)
        {
            if (strcmp_my(array_p[j], array_p[j + 1]) > 0)
            {
                str_pointer = array_p[j];
                array_p[j] = array_p[j + 1];
                array_p[j + 1] = str_pointer;
            }
        }
    }
    
    return OK;
} 
