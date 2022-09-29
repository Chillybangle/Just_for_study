#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "error_detection.h"

enum Stack_Errors stack_ctor_func (Stack* stk, ssize_t capacity, const char* name, const char* call_func, const char* call_file, ssize_t line)
{
    ASSERT_OK (stk);
    assert (!stack_error (stk));
    
    enum Stack_Errors result = Stack_Errors_FINE;
    
    if (stk -> capacity == 0)
    {
        stk -> data = (elem_type*) calloc ((size_t) capacity, sizeof (elem_type));
        stk -> capacity = capacity;
    }
    else
        result = (Stack_Errors) (result | Stack_Errors_OVERWRITING_ATTEMPT);
    
    stk -> initialization.constructed = true;
    stk -> initialization.name = name;
    stk -> initialization.call_func = call_func;
    stk -> initialization.call_file = call_file;
    stk -> initialization.line = line;
    
    ASSERT_OK(stk);
    
    return result;
}

enum Stack_Errors stack_dtor (Stack* stk)
{
    ASSERT_OK (stk);
    assert (!stack_error (stk));
    
    stk -> size = -1;
    stk -> capacity = -1;
    free (stk -> data);
    
    ASSERT_OK (stk);
    
    return Stack_Errors_FINE;
}

enum Stack_Errors stack_push (Stack* stk, elem_type value)
{
    ASSERT_OK(stk);
    assert (!stack_error (stk));
    
    enum Stack_Errors result = Stack_Errors_FINE;
    
    
    if (stk -> size >= stk -> capacity)
        result = (Stack_Errors) (result | stack_resize (stk, (stk -> capacity) * 2));
    stk -> data [stk -> size++] = value;
    
    ASSERT_OK(stk);
    
    result = verifier (stk);
    return result;
}

enum Stack_Errors stack_resize (Stack* stk, ssize_t capacity)
{
    ASSERT_OK(stk);
    assert (!stack_error (stk));
    
    if (capacity < 1)
        return print_error (Stack_Errors_ZERO_CAPACITY);
    stk -> data = (elem_type*) realloc (stk -> data, (size_t) capacity * sizeof (elem_type));
    if (stk -> data == NULL)
        return print_error (Stack_Errors_REALLOC_FAILED);
    
    ASSERT_OK(stk);
    return Stack_Errors_FINE;
}

enum Stack_Errors stack_pop (Stack* stk, elem_type* value)
{
    ASSERT_OK (stk);
    assert (!value_error (value));
    
    enum Stack_Errors result = Stack_Errors_FINE;
    
    if (stk -> size > 0)
    {
        *value = stk -> data[--(stk -> size)];
        stk -> data[(stk -> size)] = poison;
    }
    else
    {
        result = (Stack_Errors) (result | Stack_Errors_INVALID_POP);
    }
    
    if (stk -> size > stk -> capacity / 4)
        result = (Stack_Errors) (result | stack_resize (stk, (stk -> capacity) / 2));
    
    ASSERT_OK (stk);
    
    result = (Stack_Errors) (result | verifier (stk));
    return result;
}
