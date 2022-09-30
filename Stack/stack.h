#define DEBUG 4
//#define LOGALL
//0 - без дебага
//1 - дебаг
//2 - с канарейками
//3 - с хэшом
//4 - 2 + 3
//LOGALL - логи все

#include <stdbool.h>
#ifndef STACKSTRUCT
#define STACKSTRUCT

typedef int elem_type;
#define ELEM_FMT "%d"

enum Stack_Errors // binary shift
{
    Stack_Errors_FINE =                0b0,
    Stack_Errors_OVERWRITING_ATTEMPT = 0b1,
    Stack_Errors_REALLOC_FAILED =      0b10,
    Stack_Errors_STACK_NULL_PTR =      0b100,
    Stack_Errors_DATA_NULL_PTR =       0b1000,
    Stack_Errors_TOO_LARGE_SIZE =      0b10000,
    Stack_Errors_NEGATIVE_CAPACITY =   0b100000,
    Stack_Errors_NEGATIVE_SIZE =       0b1000000,
    Stack_Errors_ZERO_CAPACITY =       0b10000000,
    Stack_Errors_VALUE_NULL_PTR =      0b100000000,
    Stack_Errors_INVALID_POP =         0b1000000000,
    Stack_Errors_HASH_MISMATCH =       0b10000000000,
    Stack_Errors_HASH_WARNING =        0b100000000000,
    Stack_Errors_LEFT_CANARY_ERR =     0b1000000000000,
    Stack_Errors_RIGHT_CANARY_ERR =    0b10000000000000,
    Stack_Errors_DATA_LCANARY_ERR =    0b100000000000000,
    Stack_Errors_DATA_RCANARY_ERR =    0b1000000000000000
};

#if DEBUG>0
typedef struct
{
    bool constructed = false;
    const char* name = NULL;
    const char* call_func = NULL;
    const char* call_file = NULL;
    ssize_t line = -1;
} Varinfo;

const unsigned int DEAD_CONST = 0x1DEADFFF;
#endif

typedef struct stack
{
#if DEBUG==2 || DEBUG==4
    unsigned int left_canary = DEAD_CONST;
#endif
    
    elem_type* data = NULL;
    ssize_t size = 0;
    ssize_t capacity = 0;
    
#if DEBUG>0
    Varinfo initialization = {};
#endif
    
#if DEBUG==2 || DEBUG==4
    unsigned int right_canary = DEAD_CONST;
#endif
} Stack;

const ssize_t MIN_CAPACITY = 5;

enum Stack_Errors stack_ctor_func (Stack* stk, ssize_t capacity, const char* name, const char* call_func, const char* call_file, ssize_t line);
#define stack_ctor(stk, capacity) stack_ctor_func(stk, capacity, #stk + (#stk[0] == '&'), __PRETTY_FUNCTION__, __FILE__, __LINE__)

enum Stack_Errors stack_push (Stack* stk, elem_type value);
enum Stack_Errors stack_pop (Stack* stk, elem_type* value);
enum Stack_Errors stack_resize (Stack* stk, ssize_t capacity);
enum Stack_Errors stack_dtor (Stack* stk);

#endif
