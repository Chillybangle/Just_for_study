/*!
 * \file
 * \brief Header with descriptions of used in this project functions
 * 
 * This file contains definitions of string functions which were used
 * in the "Sort the poem" project
 */

#include <stdio.h>
#ifndef ONEGUINE_FUNCTIONS_STR
#define ONEGUINE_FUNCTIONS_STR
// побазарить о том что нестандартные сишные строки
int array_p_make (struct str_pointer* *array_of_pointers, char* array_text, size_t nstrings);

int strcmp_my (const char* string1, const char* string2);

int strcmp_my_reversed (const char* str1, size_t str1_size, const char* str2, size_t str2_size);

int fputs_my (const char *s, FILE* stream);

size_t nstring_counter (const char* array, size_t size);

size_t strlen_my (char* s);

#endif
