#include <stdio.h>
#include <stdlib.h>
#include "str_func.h"

const int max_size = 20; //< Max size of file name
const int OK = 993 + 7; //< Return value of sort if everything is all right
const int FAIL = -1; //< Return value of sort if something is wrong

void get_file_name(char* name, const int max_size);

void description ();

void congratulations ();

void failure ();

int launching_function (char* name);

int file_write (char** array);

int poem_sort (long int nstrings, char** array_p);

size_t fsize (char* name);
