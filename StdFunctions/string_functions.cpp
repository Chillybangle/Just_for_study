#include <stdio.h>
#include <cstdlib>
#include <cassert>

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

char *strchr (const char *cs, int c)
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

size_t strlen (const char *cs)
{
    assert (cs);
    
    const char *start = cs;
    while (*cs++) 
        ;
    return cs - start;
}

char *strcpy (char *s, const char *ct)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    while (*s++ = *ct++) 
        ;
    return s_init;
}

char *strncpy(char *s, const char *ct, size_t n)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    int i;
    for (i = 0; i < n && (*s++ = *ct++); i++) 
        ;
    
    if (i < n)
    {
        while (i++ < n)
            *s++ = '\0';
    }
    
    return s_init;
}

char *strcat(char *s, const char *ct)
{
    assert (s);
    assert (ct);
    
    char *s_init = s;
    while (*s)
        s++;
    
    while (*s++ = *ct++) 
        ;
    
    return s_init;
}

char *strncat(char *s, const char *ct, size_t n)
{
    assert (s);
    assert (ct);
    
    char *s_init = s; 
    while (*++s) 
        ;
    
    for (int i = 0; i < n - 1 && (*s++ = *ct++); i++) 
        ;
    
    *s = '\0';
    
    return s_init;
}

char *fgets(char *s, int n, FILE *stream)
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
        *s_copy++ = c;
    }
    *s_copy = '\0';
    
    return s;
}

char *strdup (const char *str)
{
    assert (str);
    
    char *p = (char *) malloc (strlen (str) + 1);
    if (p == NULL)
        return NULL;
    
    return strcpy (p, str);
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
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
            return -1;
    }
    
    char c = 0;
    ssize_t counter = 0;
    while ((c = fgetc (stream)) != '\n' && c != EOF)
    {
        string[counter] = c;
        counter++;
        if (counter >= *n - 1)
        {
            *n *= 2;
            string = (char *) realloc (string, *n);
            if (string == NULL)
                return -1;
            
            
            //memset (*lineptr + counter, '\0', proper_size * alloc_counter); //< memset needs to initialize remains with zeros
        }
    }
    
    string[counter] = '\n';
    counter++;
    string[counter] = '\0';
    
    *n = counter + 1; //< *n value takes into account '\0'
    string = (char*) realloc (string, *n);
    if (string == NULL)
        return -1;

    *lineptr = string;
    
    return counter;
}
