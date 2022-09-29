#include <stdio.h>
#include "stack.h"

int main ()
{
    Stack stk = {};
    
    StackCtor (&stk, 5) ASSERTED;
    StackPush (&stk, 1) ASSERTED;
    
    int value = 0;
    StackPop (&stk, &value) ASSERTED;
    
    printf ("Poped value: %d\n", value);
    
    StackDtor (&stk);
}
