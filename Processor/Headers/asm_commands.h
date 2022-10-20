#ifndef ASM_COMMANDS
#define ASM_COMMANDS
enum Commands // commands can be up to the number 31 otherwise collisions
{             // with RAM and register bits will begin
    CMD_HLT  = 0,
    CMD_PUSH = 1,
    CMD_POP  = 2,
    CMD_ADD  = 3,
    CMD_SUB  = 4,
    CMD_MUL  = 5,
    CMD_DIV  = 6,
    CMD_OUT  = 7,
    CMD_DUMP = 8,
    CMD_IN   = 9,
    CMD_DUP  = 10, //дублирует последнее значение в стеке
    CMD_JMP  = 11, //прыгает жестко четко молодежно на число 
    CMD_JB   = 12,
};
#endif
