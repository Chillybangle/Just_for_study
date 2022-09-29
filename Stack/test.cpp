#include <stdio.h>
#include "error_detection.h"
#include "stack.h"

int test ();

int main ()
{
    log_file_Ctor ();
    
    Stack stk111 = {};
    stack_ctor (&stk111, 5) ASSERTED;
    
    stack_push (&stk111, 1) ASSERTED;
    
    elem_type value = 0;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    
    printf ("%d\n", value);
    
    stack_dtor (&stk111) ASSERTED;
    log_file_Dtor ();
}
