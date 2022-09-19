#include <stdio.h> // pragma
#include <stdlib.h>
#include <assert.h>
#include "str_func.h"

#ifndef ONEGUINE_FUNCTIONS
#define ONEGUINE_FUNCTIONS
struct str_pointer
{
    char* p = NULL; //< string pointer
    size_t size = 0; //< size of string
};

const int max_size = 256; //< Max size of file name
const int OK = 993 + 7; //< Return value of sort if everything is all right
const int FAIL = -1; //< Return value of sort if something is wrong
const char name_of_sorted_file[] = "sorted.txt";

void get_file_name(char* name);

void description ();

void congratulations ();

void failure ();

int launching_function (char* name);

void file_write (FILE* sorted_file, struct str_pointer* array_p);

FILE* sorted_open ();

int original_file_write (FILE* sorted_file, char* array, size_t size_of_elem, size_t nmemb);

void bubble_sort (void* base, size_t nmemb, size_t size, int (*compar)(const void* a, const void* b));

int Strcmp_compar (const void* struct1, const void* struct2);

int Strcmp_reversed_compar (const void* struct1, const void* struct2);

size_t fsize (char* name);

#endif
