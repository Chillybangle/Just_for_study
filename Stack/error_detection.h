#include "stack.h"
#ifndef ERRORDETHEADER
#define ERRORDETHEADER

enum Mode
{
    Mode_CHECK,
    Mode_RECOUNT
};

const unsigned int POISON = 0xBADDED32;

int Error (const char* path_to_file, const int line);
void log_file_Ctor ();
void log_file_Dtor ();

enum Stack_Errors stack_error (Stack* stk);
enum Stack_Errors value_error (elem_type* value);
enum Stack_Errors verifier (Stack* stk, enum Mode Mode);
void stack_dump_func (Stack* stk, enum Stack_Errors result, const char* func, const char* file, const int line);
enum Stack_Errors print_error (enum Stack_Errors result);

unsigned int hash_ly (void* data, size_t n_elems, size_t elem_size);

#if DEBUG>0
    #define STACK_DUMP(stk, result) stack_dump_func(stk, result, __PRETTY_FUNCTION__, __FILE__, __LINE__)
    #define ASSERT_OK(stk, result) if(stack_error (stk) == Stack_Errors_FINE) STACK_DUMP(stk, result)
    #define ASSERTED == Stack_Errors_FINE || Error(__FILE__, __LINE__)
    #define FPRINT_ERR(ERROR, TEXT) if (result & ERROR) fprintf (log_file, TEXT); fflush (log_file)
#endif

#if DEBUG==0
    #define STACK_DUMP(stk, result) 
    #define ASSERT_OK(stk, result) 
    #define ASSERTED 
    #define FPRINT_ERR(ERROR, TEXT) 
#endif

#endif
