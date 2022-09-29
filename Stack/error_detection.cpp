#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "error_detection.h"
#include "stack.h"

int Error (const char* path_to_file, const int line)
{
    assert (path_to_file);
    
    if (log_file != NULL)
    {
        const char* file_name = strrchr(path_to_file, '/');
        if (file_name == NULL)
            file_name = path_to_file;
        fprintf (log_file, "Error: Function in \"%s\" file on (%d) line returns non-zero value\n", file_name, line);
        
        return 0;
    }
    
    return -1;
}

void log_file_Ctor ()
{
    log_file = fopen (stack_log_file_name, "w");
    if (log_file == NULL)
        printf ("Log file can't be open\n");
}

void log_file_Dtor ()
{
    fclose (log_file);
}

enum Stack_Errors stack_error (Stack* stk)
{
    if (stk == NULL)
    {
        fprintf (log_file, "Error: pointer to Stack struct is a NULL-pointer\n");
        
        return Stack_Errors_STACK_NULL_PTR;
    }
    
    return Stack_Errors_FINE;
}
enum Stack_Errors value_error (elem_type* value)
{
    if (value == NULL)
    {
        fprintf (log_file, "Error: pointer to value to stack_pop function is NULL\n");
        
        return Stack_Errors_VALUE_NULL_PTR;
    }
    
    return Stack_Errors_FINE;
}

enum Stack_Errors verifier (Stack* stk)
{
    enum Stack_Errors result = Stack_Errors_FINE;
    
    if (stk == NULL)
    {
        result = (Stack_Errors) (result | Stack_Errors_STACK_NULL_PTR);
    }
    else
    {
        if (stk -> data == NULL)
            result = (Stack_Errors) (result | Stack_Errors_DATA_NULL_PTR);
        if (stk -> size >= stk -> capacity)
            result = (Stack_Errors) (result | Stack_Errors_TOO_LARGE_SIZE);
        if (stk -> capacity == -1)
            result = (Stack_Errors) (result | Stack_Errors_NEGATIVE_CAPACITY);
        if (stk -> size == -1)
            result = (Stack_Errors) (result | Stack_Errors_NEGATIVE_SIZE);
    }
    
    return result;
}

void stack_dump_func (Stack* stk, const char* func, const char* file, const int line)
{
    assert (stk);
    
    if (func != NULL && file != NULL)
        fprintf (log_file, "\n%s at %s(%d):\n", func, file, line);
    else
        fprintf (log_file, "\nstack_dump_func failed: unknown calling function or (and) file\n");
    
    enum Stack_Errors result = Stack_Errors_FINE;
    result = verifier (stk);
    
    if ((stk -> initialization.constructed) == true)
    {
        if (stk -> initialization.name != NULL && stk -> initialization.call_func != NULL && 
            stk -> initialization.call_file != NULL)
        {
            fprintf (log_file, "Stack[%p] (%s) \"%s\" at %s at %s(%d)\n", 
                     stk, (result == Stack_Errors_FINE) ? "ok" : "error",
                     stk -> initialization.name, stk -> initialization.call_func,
                     stk -> initialization.call_file, line);
            if (result != Stack_Errors_FINE)
            {
                print_error (result);
            }
            fprintf (log_file,  "\t{\n"
                                "\t\tsize = %ld\n"
                                "\t\tcapacity = %ld\n"\
                                "\t\tdata[%p]\n"
                                "\t\t\t{\n",
                                stk -> size, stk -> capacity, stk);
            ssize_t i = 0;
            for (; i < stk -> size; i++)
                fprintf (log_file, "\t\t\t\t*[%ld] = " ELEM_FMT " %s\n", i, stk -> data[i], (stk -> data[i] == poison) ? "(POISON)" : "");
            for (; i < stk -> capacity; i++)
                fprintf (log_file, "\t\t\t\t[%ld] = " ELEM_FMT " %s\n", i, stk -> data[i], (stk -> data[i] == poison) ? "(POISON)" : "");
        
            fprintf (log_file, "\t\t\t}\n"
                                "\t}\n");
        }
        else
        {
            fprintf (log_file, "Stack[%p] (ok) initialize info failed\n", stk);
        }
    }
    else 
    {
        fprintf (log_file, "Stack[%p] was not constructed\n", stk);
    }
}

enum Stack_Errors print_error (enum Stack_Errors result)
{
    if (result & Stack_Errors_OVERWRITING_ATTEMPT)
        fprintf (log_file, "-Overwriting attempt (this stack has already been created, "
                           "constructor call error)\n");
    if (result & Stack_Errors_REALLOC_FAILED)
        fprintf (log_file, "-Realloc returns NULL-pointer (stack resize error)\n");
    if (result & Stack_Errors_STACK_NULL_PTR)
        fprintf (log_file, "-The pointer to a struct Stack variable is a NULL-pointer\n");
    if (result & Stack_Errors_DATA_NULL_PTR)
        fprintf (log_file, "-The buffer pointer (data) is a NULL-pointer\n");
    if (result & Stack_Errors_TOO_LARGE_SIZE)
        fprintf (log_file, "-A wild situation with Stack: size >= capacity\n");
    if (result & Stack_Errors_NEGATIVE_CAPACITY)
        fprintf (log_file, "-Stack capacity is negative! (impossible value)\n");
    if (result & Stack_Errors_NEGATIVE_SIZE)
        fprintf (log_file, "-Stack size is negative! (impossible value)\n");
    if (result & Stack_Errors_INVALID_POP)
        fprintf (log_file, "-Invalid pop. Attempt to pull out an element with a negative number\n");
    
    return result;
}
