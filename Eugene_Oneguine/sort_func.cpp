#include "Oneguine_functions.h"

static void swap_elems (void* elem1, void* elem2, size_t elem_size);

void bubble_sort (void* base, size_t nmemb, size_t size, int (*compar)(const void* a, const void* b))
{
    assert (base);
    assert (compar);
    
    for (long int i = 0; i < nmemb; i++)
    {
        for (long int j = 0; j < (nmemb - 1 - i); j++)
        {
            if (compar (base + j * size, base + (j + 1) * size) > 0)
            {
                swap_elems (base + j * size, base + (j + 1) * size, size);
            }
        }
    }
}

static void swap_elems (void* elem1, void* elem2, size_t elem_size)
{
    assert (elem1);
    assert (elem2);
    
    char* elem1_char = (char*) elem1;
    char* elem2_char = (char*) elem2;
    
    char temp = 0;
    
    for (size_t i = 0; i < elem_size; i++)
    {
        temp = *elem1_char;
        *elem1_char = *elem2_char;
        *elem2_char = temp;
        elem1_char += 1;
        elem2_char += 1;
    }
}

int Strcmp_compar (const void* struct1, const void* struct2)
{
    char* str1 = ((struct str_pointer*) struct1)->p;
    char* str2 = ((struct str_pointer*) struct2)->p;
    
    return strcmp_my (str1, str2);
}

int Strcmp_reversed_compar (const void* struct1, const void* struct2)
{
    char* str1 = ((struct str_pointer*) struct1)->p;
    char* str2 = ((struct str_pointer*) struct2)->p;
    
    size_t str1_size = ((struct str_pointer*) struct1)->size;
    size_t str2_size = ((struct str_pointer*) struct2)->size; 
    
    return strcmp_my_reversed (str1, str1_size, str2, str2_size);
}
