#include <stdio.h>
#include "error_detection.h"

// file to test the stack struct
int main ()
{
    log_file_Ctor ();
    Stack stk111 = {};
    stack_ctor (&stk111, 5) ASSERTED;
    
    stack_push (&stk111, 1.1) ASSERTED;
    stack_push (&stk111, 2.2) ASSERTED;
    stack_push (&stk111, 3.3) ASSERTED;
    stack_push (&stk111, 4.4) ASSERTED;
    stack_push (&stk111, 5.5) ASSERTED;
    stack_push (&stk111, 6.6) ASSERTED;
    stack_push (&stk111, 7.7) ASSERTED;
    stack_push (&stk111, 8.8) ASSERTED;
    stack_push (&stk111, 9.9) ASSERTED;
    stack_push (&stk111, 10.1) ASSERTED;
    
    //stk111.data = NULL; deal with it
    //stk111.data = stk111.data - 2; deal
    // stk111.capacity = stk111.capacity + 100;
    
    elem_type value = 0;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_pop (&stk111, &value) ASSERTED;
    stack_push (&stk111, 4.7) ASSERTED;
    stack_push (&stk111, 5.8) ASSERTED;
    stack_push (&stk111, 6.9) ASSERTED;
    stack_push (&stk111, 7.1) ASSERTED;
    //stk111.data [2] = 100;
    //stk111.data [-1] = 15;
    //stk111.data [stk111.capacity] = 50;
    stack_push (&stk111, 8.11) ASSERTED;
    
    stack_pop (&stk111, &value) ASSERTED;
    printf ("%lf\n", value);
    
    stack_dtor (&stk111) ASSERTED;
    log_file_Dtor ();
    //stack_dtor(&stk111);
}
