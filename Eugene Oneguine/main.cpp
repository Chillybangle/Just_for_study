#include "Oneguine_functions.h"

int main ()
{
    FILE* stream = fopen ("Eugene_Oneguine.txt", "r");//возвращаемое значение обрабоать
    int result = 0;
    
    description ();
    result = poem_sort (stream);

    if (result == OK)
        congratulations ();
    else
        failure ();
    
    fclose (stream);
    
    return 0;
}
