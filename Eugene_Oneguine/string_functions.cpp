#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Oneguine_functions.h"

static int is_punctuation (char symbol);

size_t nstring_counter (const char* array)
{
    size_t counter = 0;
    while (*array)
    {
        if (*array == '\n')
        {
            while (*(array + 1) == '\r' || *(array + 1) == '\n') //пропуск пустых строк
                array++;
            
            counter++;
        }
        
        array++;
    }
    
    return counter;
}

int array_p_make (struct str_pointer* *array_of_pointers, char* array_text, size_t nstrings) // Игнорировать пустые строчки на этом этапе (не ктдать их в массив указателей)
{
    assert (array_text);
    
    if (*array_of_pointers != NULL)
    {
        printf ("Error: array_of_pointers must be a NULL pointer\n");
        return FAIL;
    }
    
    struct str_pointer* array_p = (struct str_pointer*) calloc (nstrings + 1, sizeof (struct str_pointer));
    
    int counter = 0;
    
    array_p[counter].p = array_text;
    counter++;
    while ((counter < nstrings) && (*array_text))
    {
        if (*array_text == '\n')
        {
            while (*(array_text + 1) == '\r' || *(array_text + 1) == '\n') //skip empty strings 
                array_text++;
            
            array_p[counter].p = array_text + 1;
            counter++;
        }
        
        array_text++;
    }
    
    counter = 0;
    while (counter < nstrings - 1)
    {
        array_p[counter].size = array_p[counter + 1].p - array_p[counter].p;
        counter++;
    }
    
    array_p[counter].size = strlen_my (array_p[counter].p);
    
    *array_of_pointers = array_p;
    
    return OK;
}

int strcmp_my (char* string1, char* string2)
{
    while (*string1 == ' ')
        string1++;
    while (*string2 == ' ')
        string2++;
    
    int difference = 0;
    while (*string1 != '\n' && *string2 != '\n')
    {
        if (is_punctuation (*string1))
        {
            string1++;
            continue;
        }
        if (is_punctuation (*string2))
        {
            string2++;
            continue;
        }
        
        difference = *string1 - *string2;
        if (difference != 0)
            return difference;
        string1++;
        string2++;
    }
    
    return *string1 - *string2;
}

int strcmp_my_reversed (char* str1, size_t str1_size, char* str2, size_t str2_size)
{
    char* string1 = str1 + str1_size - 1;
    char* string2 = str2 + str2_size - 1;

    int difference = 0;
    while ((str1_size-- > 0) && (str2_size-- > 0))
    {
        if (is_punctuation (*string1))
        {
            string1--;
            continue;
        }
        if (is_punctuation (*string2))
        {
            string2--;
            continue;
        }
        
        difference = *string1 - *string2;
        
        if (difference != 0)
            return difference;
        string1--;
        string2--;
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

size_t strlen_my (char* s)
{
    size_t counter = 0;
    while (*s != '\n')
    {
        counter++;
        s++;
    }
    counter++;
    return counter;
}

static int is_punctuation (char symbol)
{
    switch (symbol)
    {
        case '\"':
        case '(':
        case ')':
        case ',':
        case ';':
        case ':':
        case '.':
        case '*':
        case '-':
        case '\'':
        case '!':
        case '?':
        case ' ':
        case '}':
        case '{':
        case '[':
        case ']':
        case '_':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
