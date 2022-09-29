#include "stack.h"
#ifndef ERRORDETHEADER
#define ERRORDETHEADER

const char stack_log_file_name[] = "stack.log";
extern FILE* log_file;
const elem_type poison = 0;
//! Required name of log file pointer is "log_file"

int Error (const char* path_to_file, const int line);
void log_file_Ctor (); //< opens log_file
void log_file_Dtor ();

enum Stack_Errors stack_error (Stack* stk);
enum Stack_Errors value_error (elem_type* value);
enum Stack_Errors verifier (Stack* stk);
void stack_dump_func (Stack* stk, const char* func, const char* file, const int line);
enum Stack_Errors print_error (enum Stack_Errors result);

#define STACK_DUMP(stk) stack_dump_func(stk, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define ASSERT_OK(stk) if(stack_error (stk) == Stack_Errors_FINE) STACK_DUMP(stk)
#define ASSERTED == Stack_Errors_FINE || Error(__FILE__, __LINE__)

#endif
