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
            counter++;
        
        array++;
    }
    
    return counter;
}

int array_p_make (struct str_pointer* *array_of_pointers, char* array_text) // Игнорировать пустые строчки на этом этапе (не ктдать их в массив указателей)
{
    assert (array_text);
    
    if (*array_of_pointers != NULL)
    {
        printf ("Error: array_of_pointers must be a NULL pointer\n");
        return FAIL;
    }
    
    //printf ("\nMEOW\n%s\n", array_text);
    
    size_t nstrings = nstring_counter (array_text);
    
    struct str_pointer* array_p = (struct str_pointer*) calloc (nstrings + 1, sizeof (struct str_pointer));
    //array_p[nstrings] = {NULL, 0};
    
    int counter = 0;
    //printf ("Живой перед циклом\n");
    array_p[counter].p = array_text;
    counter++;
    //printf ("%s\n", array_p[counter-1].p);
    //printf ("I'm alive after printf\n");
    //printf ("Значение в массиве указателей %p\n", array_p[counter - 1].p);
    int i = 0;
    while ((counter < nstrings) && (*array_text))
    {
        //printf ("Цикл провернулся %d раз\n", i);
        if (*array_text == '\n')
        {
            array_p[counter].p = array_text + 1;
            counter++;
            //printf ("-----Зашел в цикл counter = %u\n", counter);
            //printf ("%s\n",array_p[counter - 1]);
        }
        //printf ("\nmeow\n");
        array_text++;
        i++;
    }
    //printf ("Вышел из цикла\n");
    counter = 0;
    while (counter < nstrings - 1)
    {
        array_p[counter].size = array_p[counter + 1].p - array_p[counter].p;
        counter++;
    }
    //printf ("Жив после вайл\n");
    //printf ("pointer of counter %p\n", array_p[counter].p);
    array_p[counter].size = strlen_my (array_p[counter].p);
    
    *array_of_pointers = array_p;
    
    //printf ("Вышел из цикла\n");
    return OK;
}

int strcmp_my (char* string1, char* string2)
{
    while (*string1 == ' ') // isspace
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
    //putchar (*string1);
    //putchar ('\n');
    //putchar (*string2);
    //putchar ('\n');
    
    //printf ("size of 1 string: %d\nsize of 2 string: %d\n", str1_size, str2_size);
    
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
        //printf ("difference: %d\n", difference);
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
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
