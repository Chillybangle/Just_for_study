#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include "string_functions.h"
#include "Oneguine_functions.h"

int puts_my (const char *s)
{
    assert (s);
    
    while (*s) 
    {
        if (putchar (*s++) == EOF)
            return EOF;
    }
    
    return putchar ('\n');
}

char *strchr_my (const char *cs, int c)
{
    assert (cs);
    
    while (*cs != c)
    {
        if (*cs == '\0')
            return NULL;
        
        cs++;
    }
    return (char *) cs;
}

size_t strlen_my (const char *cs)
{
    assert (cs);
    
    const char *start = cs;
    while (*cs++) 
        ;
    
    return (size_t) (cs - start);
}

char *strcpy_my (char *s, const char *ct)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    while ((*s++ = *ct++)) 
        ;
    return s_init;
}

char *strncpy_my (char *s, const char *ct, size_t n)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    size_t i;
    for (i = 0; i < n && (*s++ = *ct++); i++) 
        ;
    
    if (i < n)
    {
        while (i++ < n)
            *s++ = '\0';
    }
    
    return s_init;
}

char *strcat_my (char *s, const char *ct)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    while (*s)
        s++;
    
    while ((*s++ = *ct++)) 
        ;
    
    return s_init;
}

char *strncat_my (char *s, const char *ct, size_t n)
{
    assert (s);
    assert (ct);
    
    char *s_init = s; 
    while (*++s) 
        ;
    
    for (size_t i = 0; i < n - 1 && (*s++ = *ct++); i++) 
        ;
    
    *s = '\0';
    
    return s_init;
}

char *fgets_my (char *s, int n, FILE *stream)
{
    assert (s);
    
    int c = 0;
    char *s_copy = s;
    for (int i = 0; i < (n - 1) && (c = fgetc (stream)) != '\n'; i++)
    {
        if (c == EOF)
        {
            *s_copy = '\0';
            return NULL;
        }
        *s_copy++ = (char) c;
    }
    *s_copy = '\0';
    
    return s;
}

char *strdup_my (const char *str)
{
    assert (str);
    
    char *p = (char *) malloc (strlen_my (str) + 1);
    if (p == NULL)
        return NULL;
    
    return strcpy_my (p, str);
}

ssize_t getline_my (char **lineptr, size_t *n, FILE *stream)
{
    assert (lineptr);
    assert (n);
    assert (stream);

    char *string = *lineptr;
    const size_t PROPER_SIZE = 100; //< Size for memory allocation
    
    if (string == NULL) 
    {
        if (*n == 0)
            *n = PROPER_SIZE;
        
        string = (char *) calloc (*n, sizeof (char));

        if (string == NULL)
            return FAIL;
    }
    
    int c = 0;
    size_t counter = 0;
    while ((c = fgetc (stream)) != '\n' && c != EOF)
    {
        string[counter] = (char) c;
        counter++;
        if (counter >= *n - 1)
        {
            *n *= 2;
            string = (char *) realloc (string, *n);
            if (string == NULL)
                return FAIL;
        }
    }
    
    string[counter] = '\n';
    counter++;
    string[counter] = '\0';
    
    *n = counter + 1; //< *n value takes into account '\0'
    string = (char*) realloc (string, *n);
    if (string == NULL)
        return FAIL;

    *lineptr = string;
    
    return (ssize_t) counter;
}
