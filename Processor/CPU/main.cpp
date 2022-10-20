//Проверка, нормальный ли файл нам передали
//Проверка версии процессора и скомпилированного файла
//заказ массива надлежащего размера
//чтение в массив
//работа со стеком
#include <stdio.h>
#include <stack.h>
#include <error_detection.h>
#include <assert.h>
#include <stdlib.h>
#include "Errors.h"
#include "asm.h"
#include "cpu.h"
#include "asm_commands.h"

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf ("Invalid CPU call\n");
        return -1;
    }
    FILE* program_file = fopen (argv[1], "r");
    if (program_file == NULL)
    {
        printf ("File opening error\n");
        return -1;
    }
    
    enum CPU_Errors result = CPU_Errors_NICE;
    size_t cmd_amount = 0;
    result = preprocessing_check (program_file, &cmd_amount);
    if (result != CPU_Errors_NICE)
    {
        error_out (result);
        return -1;
    }
    
    num_type* cmd_arr = read_file (program_file, cmd_amount);
    
    for (int i = 0; i < cmd_amount; i++)
    {
        printf ("%d\n", cmd_arr[i]);
    }
    
    cmd_processing (cmd_arr, cmd_amount);

    free (cmd_arr);
    return 0;
}

enum CPU_Errors preprocessing_check (FILE* program_file, size_t* cmd_amount)
{
    struct compile_info c_info;
    size_t get_signature = 0;
    size_t get_version = 0;
    //fscanf (program_file, "%lu %lu %lu", &get_signature, &get_version, &c_info.size);
    fread ((void*) &get_signature, sizeof (size_t), 1, program_file);
    fread ((void*) &get_version, sizeof (size_t), 1, program_file);
    fread ((void*) &c_info.size, sizeof (size_t), 1, program_file);
    //printf ("%lu\n", c_info.size);
    
//     printf ("%x\n", get_signature);
//     printf ("%d\n", get_version);
    if (get_signature != c_info.signature)
    {
        return CPU_Errors_INVALID_FFORMAT;
    }
    
    if (get_version != c_info.version)
    {
        return CPU_Errors_INVALID_VERSION;
    }
    
    *cmd_amount = c_info.size;
    
    return CPU_Errors_NICE;
}

num_type* read_file (FILE* program_file, size_t cmd_amount)
{
    assert (program_file);
    
    num_type* cmd_arr = (num_type*) calloc (cmd_amount, sizeof (num_type));
    if (cmd_arr == NULL)
        return NULL;
    
    //printf ("Пропуск %d %d %d байт в начале файла\n", sizeof (unsigned int),  sizeof (int),  sizeof (size_t));
    
    
    fseek(program_file, 3*sizeof (size_t), SEEK_SET);
    //if (
        fread ((void*) cmd_arr, sizeof (num_type), cmd_amount, program_file); //!= (cmd_amount / sizeof (num_type)))
    //{
      //  printf ("Reading fail. The number of elements does not match the declared one\n");
        //return NULL;
    //}
    
    return cmd_arr;
}

enum CPU_Errors cmd_processing (num_type* cmd_arr, size_t cmd_amount)
{
    log_file_Ctor ();
    Stack stk = {};
    stack_ctor (&stk, cmd_amount) ASSERTED;
    
    num_type regs[5] = {0};         //--CPU registers--
                                    //  1   2   3   4
                                    // rax rbx rcx rdx
    
    num_type RAM[RAM_SIZE] = {0};   //---RAM array---
    
    num_type value1 = 0;
    num_type value2 = 0;
    for (size_t ip = 0; cmd_arr[ip] != 0 && ip < cmd_amount; ip++)
    {
        int cur_cmd = cmd_arr[ip];
        
        cmd_dump (cur_cmd);
        
        switch (cur_cmd & 0x1F) //mask for the right 5 bits
        {
            case CMD_PUSH:
            {
                //printf ("CMD_PUSH label\n");
                num_type arg = 0;
                if (cur_cmd & 0x20) arg += cmd_arr[++ip];
                if (cur_cmd & 0x40) arg += regs[(int) cmd_arr[++ip]];
                if (cur_cmd & 0x80) arg = RAM[(int) arg];
                
                stack_push (&stk, arg) ASSERTED;
                break;
            }
            case CMD_POP:
            {
                stack_pop (&stk, &value1) ASSERTED;
                
                int index = 0;
                if (cur_cmd & 0x80)
                {
                    if (cur_cmd & 0x20) index += cmd_arr[++ip];
                    if (cur_cmd & 0x40) index += regs[(int) cmd_arr[++ip]];
                    //printf ("index = %d value = %d\n", index, value1);
                    RAM[index] = value1;
                }
                else if (cur_cmd & 0x40)
                {
                    index += cmd_arr[++ip];
                    regs[index] = value1;
                }
                else
                {
                    printf ("Pop value error\n");
                    return CPU_Errors_POP_VALUE_ERR;
                }
                
                value1 = 0;
                break;
            }
            case CMD_ADD:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_pop (&stk, &value2) ASSERTED;
                value1 += value2;
                stack_push (&stk, value1) ASSERTED;
                value1 = value2 = 0;
                break;
            }
            case CMD_SUB:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_pop (&stk, &value2) ASSERTED;
                value1 -= value2;
                stack_push (&stk, value1) ASSERTED;
                value1 = value2 = 0;
                break;
            }
            case CMD_MUL:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_pop (&stk, &value2) ASSERTED;
                value1 *= value2;
                stack_push (&stk, value1) ASSERTED;
                value1 = value2 = 0;
                break;
            }
            case CMD_DIV:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_pop (&stk, &value2) ASSERTED;
                value1 = value2 / value1;
                stack_push (&stk, value1) ASSERTED;
                value1 = value2 = 0;
                break;
            }
            case CMD_OUT:
            {
                stack_pop (&stk, &value1) ASSERTED;
                printf ("Out value: " NUM_FMT "\n", value1);
                value1 = value2 = 0;
                break;
            }
            case CMD_DUP:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_push (&stk, value1) ASSERTED;
                stack_push (&stk, value1) ASSERTED;
                value1 = 0;
                break;
            }
            case CMD_JMP:
            {
                ip = cmd_arr[ip + 1] - 1; // поправка на счетчик for
                //printf ("CMD_JMP: %d", ip);
                break;
            }
            case CMD_DUMP:
            {
                dump_func (cmd_arr, cmd_amount, ip, &stk);
                break;
            }
            case CMD_JB:
            {
                stack_pop (&stk, &value1) ASSERTED;
                stack_pop (&stk, &value2) ASSERTED;
                if (value2 > value1)
                    ip = cmd_arr[ip + 1] - 1;
                break;
            }
            default:
            {
                stack_dtor (&stk) ASSERTED;
                log_file_Dtor ();
                printf ("Unknwown command \"%d\". Emergency shutdown\n", cmd_arr[ip]);
                return CPU_Errors_UNKNOWN_COMMAND;
            }
        }
            
    }
    
    stack_dtor (&stk) ASSERTED;
    log_file_Dtor ();
    
    return CPU_Errors_NICE;
}

void error_out (enum CPU_Errors result)
{
    switch ((int) result)
    {
        case CPU_Errors_INVALID_FFORMAT:
            printf ("Invalid file format. Please, enter the file processed by asm\n");
            break;
        case CPU_Errors_INVALID_VERSION:
            printf ("The file version does not match the cpu version. Please, recompile the source code\n");
            break;
        default:
            printf ("Unknwown error\n");
            break;
    }
}

void dump_func (num_type* arr, size_t cmd_amount, size_t cur_ip, const Stack* stk)
{
    for (size_t i = 0; i < cmd_amount; i++)
    {
        printf ("%02lu ", i);
    }
    putchar ('\n');
    
    for (size_t i = 0; i < cmd_amount; i++)
    {
        printf ("%2d ", arr[i]);
    }
    putchar ('\n');
    
    for (size_t i = 0; i < cur_ip; i++)
    {
        putchar ('_');
        putchar ('_');
        putchar ('_');
    }
    putchar ('^');
    printf ("IP = %lu\n", cur_ip);
    
    for (size_t i = 0; i < (stk -> size); i++)
    {
        printf ("[%lu] = " NUM_FMT " \n", i, (stk -> data)[i]);
    }
}
