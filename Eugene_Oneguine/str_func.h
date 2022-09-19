#include <stdio.h>

int array_p_make (struct str_pointer* *array_of_pointers, char* array_text);

int strcmp_my (char* string1, char* string2);

int strcmp_my_reversed (char* str1, size_t str1_size, char* str2, size_t str2_size);

int fputs_my (const char *s, FILE* stream);

size_t nstring_counter (const char* array);
