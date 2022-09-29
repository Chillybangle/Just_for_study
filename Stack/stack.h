#include <stdbool.h>
#ifndef STACKSTRUCT
#define STACKSTRUCT

typedef int elem_type;
#define ELEM_FMT "%d"

enum Stack_Errors: int
{
    Stack_Errors_FINE = 0,
    Stack_Errors_OVERWRITING_ATTEMPT = 1,
    Stack_Errors_REALLOC_FAILED = 2,
    Stack_Errors_STACK_NULL_PTR = 4,
    Stack_Errors_DATA_NULL_PTR = 8,
    Stack_Errors_TOO_LARGE_SIZE = 16,
    Stack_Errors_NEGATIVE_CAPACITY = 32,
    Stack_Errors_NEGATIVE_SIZE = 64,
    Stack_Errors_ZERO_CAPACITY = 128,
    Stack_Errors_VALUE_NULL_PTR = 256,
    Stack_Errors_INVALID_POP = 512
};

typedef struct varinfo
{
    bool constructed = false;
    const char* name = NULL;
    const char* call_func = NULL;
    const char* call_file = NULL;
    ssize_t line = -1;
} Varinfo;

typedef struct stack
{
    elem_type* data = NULL;
    ssize_t size = 0;
    ssize_t capacity = 0;
    Varinfo initialization = {};
} Stack;

enum Stack_Errors stack_ctor_func (Stack* stk, ssize_t capacity, const char* name, const char* call_func, const char* call_file, ssize_t line);
#define stack_ctor(stk, capacity) stack_ctor_func(stk, capacity, #stk + 1, __PRETTY_FUNCTION__, __FILE__, __LINE__)

enum Stack_Errors stack_push (Stack* stk, elem_type value);
enum Stack_Errors stack_pop (Stack* stk, elem_type* value);
enum Stack_Errors stack_resize (Stack* stk, ssize_t capacity);
enum Stack_Errors stack_dtor (Stack* stk);

#endif
