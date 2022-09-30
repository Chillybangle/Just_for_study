#include <stdio.h>
#include "meow.h"

int test ()
{
    stream = fopen ("test.txt", "w");
    fprintf (stream, "meow\n");
    fclose (stream);
    //return i;
}
