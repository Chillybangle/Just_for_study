#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int OK = 993 + 7; //< Return value of sort if everything is all right
const int FAIL = -1; //< Return value of sort if something is wrong

int poem_sort (FILE* stream);

void description ();
void congratulations ();
void failure ();
