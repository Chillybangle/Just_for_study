#include <stdio.h>
#include <stdlib.h>
#include "string_functions.h"

int main ()
{
    const char ct[] = "Test string";
    char s[100] = {'C', 'a', 't', EOF, 'a'};
    size_t n = 0;
    FILE *test = fopen ("test.txt", "r");
    char *lineptr = NULL;//(char *) calloc (100, sizeof (char));
    size_t ret_val = getline (&lineptr, &n, test);
    printf ("%s n = %d ret_val = %d", lineptr, n, ret_val);
    free (lineptr);
    
    // puts_my (ct);
    //free (lineptr);
    /*getline (test, s, 5, ";");
    fclose (test);
    //char *p = strdup (ct);
    printf ("%s\n", s);
    */
    //puts (s);
} 
