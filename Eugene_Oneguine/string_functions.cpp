#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Oneguine_functions.h"

size_t nstring_counter (const char* array)
{
    size_t counter = 0;
    while (*array)
    {
        if (*array == '\n')
            counter++;
        
        array++;
    }
    
    return counter;
}

int array_p_make (char* **array_of_pointers, char* array_text)
{
    assert (array_text);
    
    if (*array_of_pointers != NULL)
    {
        printf ("Error: array_of_pointers must be a NULL pointer\n");
        return FAIL;
    }
    
    //printf ("\nMEOW\n%s\n", array_text);
    
    size_t nstrings = nstring_counter (array_text);
    
    char** array_p = (char**) calloc (nstrings + 1, sizeof (char*));
    array_p[nstrings] = NULL;
    
    int counter = 0;
    //printf ("Живой перед циклом\n");
    array_p[counter] = array_text;
    counter++;
    //printf ("%s\n", array_p[counter]);
    //printf ("Значение в массиве указателей %p\n", array_p[counter - 1]);
    //int i = 0;
    while ((counter < nstrings) && (*array_text))
    {
        //printf ("Цикл провернулся %d раз\n", i);
        if (*array_text == '\n')
        {
            array_p[counter] = array_text + 1;
            counter++;
            //printf ("-----Зашел в цикл counter = %u\n", counter);
            //printf ("%s\n",array_p[counter - 1]);
        }
        //printf ("\nmeow\n");
        array_text++;
        //i++;
    }
    
    *array_of_pointers = array_p;
    
    //printf ("Вышел из цикла\n");
    return OK;
}

int strcmp_my (char* string1, char* string2)
{
    int difference = 0;
    while (*string1 != '\n' && *string2 != '\n')
    {
        difference = *string1 - *string2;
        if (difference != 0)
            return difference;
        string1++;
        string2++;
    }
    
    return *string1 - *string2;
}

int fputs_my (const char *s, FILE* stream)
{
    assert (s);
    
    while (*s != '\n') 
    {
        if (fputc (*s++, stream) == EOF)
            return EOF;
    }
    
    return fputc ('\n', stream);
}
