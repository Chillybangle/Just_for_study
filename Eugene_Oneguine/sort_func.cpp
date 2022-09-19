#include "Oneguine_functions.h"

static void swap_elems (void* elem1, void* elem2, size_t elem_size);

void bubble_sort (void* base, size_t nmemb, size_t size, int (*compar)(const void* a, const void* b))
{
    assert (base);
    assert (compar);
    char* base_ch = (char*) base;
    
    for (size_t x = 0; x < nmemb; x++)
    {
        for (size_t y = 0; y < (nmemb - 1 - x); y++)
        {
            if (compar ((void*) (base_ch + y * size), (void*) (base_ch + (y + 1) * size)) > 0)
            {
                swap_elems ((void*) (base_ch + y * size), (void*) (base_ch + (y + 1) * size), size);
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
    size_t* elem1_st = (size_t*) elem1;
    size_t* elem2_st = (size_t*) elem2;
    
    char temp_char = 0;
    size_t temp_st = 0;
    size_t st_size = sizeof (size_t);
    
    for (size_t counter = 0; counter < elem_size; counter++)
    {
        if ((elem_size - counter) > st_size)
        {
            temp_st = *elem1_st;
            *elem1_st = *elem2_st;
            *elem2_st = temp_st;
            
            elem1_char += st_size;
            elem2_char += st_size;
            elem1_st += 1;
            elem2_st += 1;
            
            counter += st_size - 1;
        }
        else
        {
            temp_char = *elem1_char;
            *elem1_char = *elem2_char;
            *elem2_char = temp_char;
            
            elem1_char += 1;
            elem2_char += 1;
        }
    }
}

int Strcmp_compar (const void* struct1, const void* struct2)
{
    assert (struct1);
    assert (struct2);
    
    char* str1 = ((const struct str_pointer*) struct1)->p;
    char* str2 = ((const struct str_pointer*) struct2)->p;
    
    return strcmp_my (str1, str2);
}

int Strcmp_reversed_compar (const void* struct1, const void* struct2)
{
    assert (struct1);
    assert (struct2);
    
    char* str1 = ((const struct str_pointer*) struct1)->p;
    char* str2 = ((const struct str_pointer*) struct2)->p;
    
    size_t str1_size = ((const struct str_pointer*) struct1)->size;
    size_t str2_size = ((const struct str_pointer*) struct2)->size; 
    
    return strcmp_my_reversed (str1, str1_size, str2, str2_size);
}
