#include <stdio.h>
#include "error_detection.h"

int main ()
{
    log_file_Ctor ();
    Stack stk111 = {};
    stack_ctor (&stk111, 5) ASSERTED;
    
    stack_push (&stk111, 1) ASSERTED;
    stack_push (&stk111, 2) ASSERTED;
    stack_push (&stk111, 3) ASSERTED;
    stack_push (&stk111, 4) ASSERTED;
    stack_push (&stk111, 5) ASSERTED;
    stack_push (&stk111, 6) ASSERTED;
    stack_push (&stk111, 7) ASSERTED;
    stack_push (&stk111, 8) ASSERTED;
    stack_push (&stk111, 9) ASSERTED;
    stack_push (&stk111, 10) ASSERTED;
    
    // stk111.data = NULL;
    // stk111.data = stk111.data - 2;
    // stk111.capacity = stk111.capacity + 100;
    
    elem_type value = 0;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_push (&stk111, 4) ASSERTED;
    stack_push (&stk111, 5) ASSERTED;
    stack_push (&stk111, 6) ASSERTED;
    stack_push (&stk111, 7) ASSERTED;
    stk111.data [2] = 100;
    stk111.data [-1] = 15;
    stk111.data [stk111.capacity] = 50;
    stack_push (&stk111, 8) ASSERTED;
    
    printf ("%d\n", value);
    printf ("%d\n", Stack_Errors_REALLOC_FAILED);
    
    stack_dtor (&stk111) ASSERTED;
    log_file_Dtor ();
    // stack_dtor(&stk111);
}
