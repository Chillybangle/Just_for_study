//считать онегинским способом
//создать массив кол-во строк х2 в исходнике, записать в него исходник, пользоваться им
//Подсчитать количество чисел в скомпилированном файле
//В начале скомпилированного файла вставить сигнатуру, версию, кол-во чисел
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "asm_commands.h"
#include "asm.h"

const char* DEFAULT_TXT_NAME = "../a.txt";
const char* DEFAULT_BIN_NAME = "../b.bin";

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        if (argc != 3)
        {
            printf ("Input the source file name as command line argument (+optional: name of compiled file)\n");
            return -1;
        }
    }
    
    size_t nlines = 0;
    
    char* array_text = NULL;
    struct str_pointer* array_line_ptrs = read_source (argv[1], &nlines, &array_text);
    num_type* result_arr = (num_type*) calloc (nlines * 2, sizeof (num_type));
    //printf ("%s\n", array_line_ptrs[0].p);
    
    struct compile_info c_info;
    
    int convert_result = 0;
    struct Labels* labels = labels_make();
    //printf ("labels after create: %d\n", labels[0].address);
    
    convert_result = convert_to_asm (array_line_ptrs, nlines, result_arr, &c_info, labels);
    convert_result = convert_to_asm (array_line_ptrs, nlines, result_arr, &c_info, labels);
    
    if (convert_result == 0)
    {
        if (argc == 3)
            bin_file_out (result_arr, c_info, argv[2]);
        else
            bin_file_out (result_arr, c_info, NULL);
    }
    else
    {
        printf ("Compilation failed. File was not created\n");
    }
    
    //printf ("%d %d %d %d\n", *result_arr, *(result_arr + 1), *(result_arr + 2), *(result_arr + 3));
    labels_delete (labels);
    free (array_line_ptrs);
    free (result_arr);
    free (array_text);
}

struct str_pointer* read_source (char* source_name, size_t* nlines, char** array_text)
{
    FILE* input_stream = fopen (source_name, "r");
    if (input_stream == NULL)
    {
        perror ("Error: I can't open a file with this name");
        return NULL;
    }
    
    size_t size = fsize (source_name);
    if (size == 0)
    {
        printf ("Error: I can't get the file size\n");
        return NULL;
    }
    
    *array_text = (char*) calloc (size + 1, sizeof (char)); // \0 symbol in the end
    
    fread (*array_text, sizeof(char), size, input_stream);
    if (ferror (input_stream))
    {
        printf ("Error: I can't read the file\n");
        return NULL;
    }
    
    
    *nlines = nstring_counter (*array_text, size);
    
    printf ("nlines: %d\n", *nlines);
    
    struct str_pointer* array_p = NULL;
    if (array_p_make (&array_p, *array_text, *nlines) == -1)
        return NULL;
    //printf ("%s\n", array_p[0].p);
    
    fclose (input_stream);
    
    //printf ("Array_p is %p\n", array_p);
    return array_p;
}

int convert_to_asm (struct str_pointer* array_line_ptrs, size_t nlines, num_type* result_arr, struct compile_info* c_info, struct Labels* labels)
{
    static int compile_number = 0;
    
    char cmd[21] = "";
    size_t lcounter = 0;
    
    int nread_symb = 0;
    int add_nread = 0;
    int cmd_flags = 0;
    
    num_type val = 0;
    size_t commands_amount = 0;
    int where_to_jump = -1;
    
#ifdef TXT_OUT
    FILE* txt_file = NULL;
    txt_file = fopen (DEFAULT_TXT_NAME, "w");
#endif
    
    //FILE* listing = fopen ("../listing.txt", "w");
    
    while (lcounter < nlines)
    {
        comment_pass (array_line_ptrs[lcounter].p);
        sscanf (array_line_ptrs[lcounter].p, "%20s %n", cmd, &nread_symb);
        if (array_line_ptrs[lcounter].p[0] == '\0')
        {
            lcounter++;
            //printf ("Loop skipping, cmd = %s\n", cmd);
            continue;
        }
        
        if (label_check (cmd, labels, commands_amount) == 0)
        {
            lcounter++;
            continue;
        }
        
        if (stricmp (cmd, "push") == 0)
        {
            if (get_args (array_line_ptrs[lcounter].p, nread_symb, &val, &add_nread, &cmd_flags) != 0)
            {
                printf ("Wrong argument \'%s\' of push function in \'%s\' line\n", array_line_ptrs[lcounter].p + nread_symb, array_line_ptrs[lcounter].p);
                return -1;
            }
            
            *result_arr++ = CMD_PUSH | cmd_flags;
            //printf ("push value: %x\n", *(result_arr - 1));
            *result_arr++ = val;
            commands_amount += 2;
            TXT_FILE_PRINT2 (CMD_PUSH | cmd_flags, NUM_FMT);
            
            val = 0;
        }
        else if (stricmp (cmd, "pop") == 0)
        {
            if (get_args (array_line_ptrs[lcounter].p, nread_symb, &val, &add_nread, &cmd_flags) != 0)
            {
                printf ("Wrong argument \'%s\' of pop function in \'%s\' line\n", array_line_ptrs[lcounter].p + nread_symb, array_line_ptrs[lcounter].p);
                return -1;
            }
            
            *result_arr++ = CMD_POP | cmd_flags;
            //printf ("pop value: %x\n", *(result_arr - 1));
            *result_arr++ = val;
            commands_amount += 2;
            TXT_FILE_PRINT2 (CMD_POP | cmd_flags, NUM_FMT);
            
            val = 0;
        }
        else if (stricmp (cmd, "add") == 0)
        {
            *result_arr++ = CMD_ADD;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_ADD);
        }
        else if (stricmp (cmd, "sub") == 0)
        {
            *result_arr++ = CMD_SUB;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_SUB);
        }
        else if (stricmp (cmd, "mul") == 0)
        {
            *result_arr++ = CMD_MUL;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_MUL);
        }
        else if (stricmp (cmd, "div") == 0)
        {
            *result_arr++ = CMD_DIV;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_DIV);
        }
        else if (stricmp (cmd, "out") == 0)
        {
            *result_arr++ = CMD_OUT;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_OUT);
        }
        else if (stricmp (cmd, "dump") == 0)
        {
            *result_arr++ = CMD_DUMP;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_DUMP);
        }
        else if (stricmp (cmd, "in") == 0)
        {
            *result_arr++ = CMD_IN;
            *result_arr++ = 0;
            commands_amount += 2;
            TXT_FILE_PRINT2 (CMD_IN, NUM_FMT);
        }
        else if (stricmp (cmd, "hlt") == 0)
        {
            *result_arr++ = CMD_HLT;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_HLT);
        }
        else if (stricmp (cmd, "dup") == 0)
        {
            *result_arr++ = CMD_DUP;
            commands_amount++;
            TXT_FILE_PRINT1 (CMD_DUP);
        }
        else if (stricmp (cmd, "jmp") == 0)
        {
            if (get_args_jmp (array_line_ptrs[lcounter].p, nread_symb, &val, &add_nread, compile_number, labels) != 0)
                return -1;
            
            *result_arr++ = CMD_JMP;
            *result_arr++ = val;
            commands_amount += 2;
            TXT_FILE_PRINT2 (CMD_JMP, NUM_FMT);
            
            val = 0;
        }
        else if (stricmp (cmd, "jb") == 0)
        {
            if (get_args_jmp (array_line_ptrs[lcounter].p, nread_symb, &val, &add_nread, compile_number, labels) != 0)
                return -1;
            
            *result_arr++ = CMD_JB;
            *result_arr++ = val;
            commands_amount += 2;
            TXT_FILE_PRINT2 (CMD_JB, NUM_FMT);
            
            val = 0;
        }
        else
        {
            printf ("Wrong command \'%s\' in string \'%s\'. Compilation failed.\n", cmd, array_line_ptrs[lcounter].p);
            return -1;
        }
        
        //printf ("%d %d\n", nread_symb, add_nread);
        
        if (space_symbols (array_line_ptrs[lcounter].p + nread_symb + add_nread) != 0)
        {
            printf ("Invalid input \'%s\' command in string \'%s\'\n", array_line_ptrs[lcounter].p + nread_symb + add_nread, array_line_ptrs[lcounter].p);
            return -1;
        }
        
        //cmd[0] = '\0';
        add_nread = 0;
        cmd_flags = 0;
        lcounter++;
    }
    
#ifdef TXT_OUT
    fclose (txt_file);
#endif
    
    compile_number++;
    //fclose (listing);
    c_info -> size = commands_amount;
    return 0;
}

int bin_file_out (num_type* result_arr, struct compile_info c_info, const char* bin_file_name)
{
    assert (result_arr);
    
    if (bin_file_name == NULL)
        bin_file_name = DEFAULT_BIN_NAME;
    else
    {
        int name_size = strlen (bin_file_name);
        char* temp = (char*) calloc (name_size + 4, sizeof(char));
        temp = strcat (temp, "../");
        bin_file_name = strcat (temp, bin_file_name);
    }
    
    FILE* bin_file = fopen (bin_file_name, "w");
    //printf ("Тутачки\n");
    if (bin_file == NULL)
    {
        perror ("Bin file opening error");
        return -1;
    }
    
    //printf ("Записал1\n");
    //fprintf (bin_file, "%x %d %lu", c_info.signature, c_info.version, c_info.size);
    //size_t info_arr[] = {c_info.signature, c_info.version, c_info.size};
    fwrite ((void*) &c_info, sizeof (c_info), 1, bin_file);
    fwrite ((void*) result_arr, sizeof (num_type), c_info.size, bin_file);
    //printf ("Записал2\n");
    
    
    fclose (bin_file);
    
    return 0;
}

int space_symbols (const char* string)
{
    while (*string)
        if (isspace (*string++) == 0)
            return -1;
        
    return 0;
}

void comment_pass (char* string)
{
    char* comment_start_pointer = strchr (string, ';');
    if (comment_start_pointer != NULL)
    {
        *comment_start_pointer++ = '\0'; // the comment in the line starts with ;
        *comment_start_pointer = '\0';
    }
}

struct Labels* labels_make()
{
    struct Labels* labels = (struct Labels*) calloc (MAX_LABELS_NUM + 1, sizeof (struct Labels));
    for (int i = 0; i < MAX_LABELS_NUM + 1; i++)
    {
        labels[i].address = LABEL_POISON;
    }
    
    return labels;
}

void labels_delete (struct Labels* labels)
{
    free (labels);
}

size_t find_label (struct Labels* labels, int read_label)
{
    size_t result = LABEL_POISON;
    if (read_label > MAX_LABELS_NUM)
    {
        printf ("Invalid label number. Please, create labels up to a number %d\n", MAX_LABELS_NUM);
        return result;
    }
    if (labels[read_label].address != LABEL_POISON)
    {
        //printf ("meow");
         result = labels[read_label].address;
    }
    
    return result;
}

int label_check (const char* cmd, struct Labels* labels, size_t commands_amount)
{
    int i = 0;
    while (isspace(cmd[i]))
    {
        i++;
    }
    
    int label_number = -1;
    if (cmd[i] == ':')
        if (sscanf (cmd + i + 1, "%d", &label_number) == 1)
        {
            labels[label_number].address = commands_amount;
            //printf ("address in the label: %d\n", labels[label_number].address);
            return 0;
        }
        else
        {
            printf ("Invalid label input\n");
        }
    
    return -1;
}

int get_args (char* string, int nread_symb, num_type* val, int* add_nread, int* cmd_flags)
{
    char temp_storage[21] = "";
    if (sscanf (string + nread_symb, NUM_FMT " %n", val, add_nread) == 1)
    {
        *cmd_flags = *cmd_flags | ARG_IMMED;
        return 0;
    }
    if (sscanf (string + nread_symb, "%s %n", temp_storage, add_nread) != 1)
        return -1;
    
    if (temp_storage[0] != '\0')
    {
        int sq_bracket_corr = 0;
        if (temp_storage[0] == '[')
        {
            *cmd_flags = *cmd_flags | ARG_RAM;
            char* sq_br_ptr = strchr (temp_storage + 1, ']');
            if (sq_br_ptr == NULL)
            {
                printf ("Invalid input format\n");
                return -1;
            }
            *sq_br_ptr = '\0';
            //*add_nread += 2;
            sq_bracket_corr++;
        }
        
        num_type result = 0;
        int determ_arg_res = determ_arg (temp_storage + sq_bracket_corr, add_nread, cmd_flags, &result);
        if (determ_arg_res >= 0)
             if (determ_arg_res == 0)
                 *val = result;
             else
                 *val = determ_arg_res;
        else
        {
            printf ("Error determing arguments\n");
            return -1;
        }
    }
    
    return 0;
}

int determ_arg (char* str, int* add_nread, int* cmd_flags, num_type* result)
{
    const int first  = 1;
    const int second = 2;
    const int third  = 3;
    const int fourth  = 4;
    
    //char temp_storage[21] = "";
    //printf ("Hi\n");
    //printf ("%s\n", str);
    if (stricmp (str, "rax") == 0)
    {
        //printf ("Зашел в rax\n");
        //*add_nread += 3;
        *cmd_flags = *cmd_flags | ARG_REG;
        return first;
    }
    if (stricmp (str, "rbx") == 0)
    {
        //*add_nread += 3;
        *cmd_flags = *cmd_flags | ARG_REG;
        return second;
    }
    if (stricmp (str, "rcx") == 0)
    {
        //*add_nread += 3;
        *cmd_flags = *cmd_flags | ARG_REG;
        return third;
    }
    if (stricmp (str, "rdx") == 0)
    {
        //*add_nread += 3;
        *cmd_flags = *cmd_flags | ARG_REG;
        return fourth;
    }
    
    num_type temp_immediate = -1;
    int temp_add_nread = 0;
    if (sscanf (str, NUM_FMT " %n", &temp_immediate, &temp_add_nread) == 1)
    {
        *cmd_flags = *cmd_flags | ARG_IMMED;
        *result = temp_immediate;
        //*add_nread += temp_add_nread;
        return 0;
    }
    
    return -1;
}

int get_args_jmp (char* string, int nread_symb, num_type* val, int* add_nread, int compile_number, struct Labels* labels)
{
    int i = 0;
    while (isspace(string[i]))
        i++;
    
    if (string[i] == 'j')
    {
        int read_label = LABEL_POISON;
        num_type where_to_jump = -1;
        //printf ("where_to_jump before scanf %d\n", where_to_jump);
        if (sscanf (string + nread_symb, "%d %n", &where_to_jump, add_nread) != 1)
        {
            //printf ("where_to_jump after scanf %d\n", where_to_jump);
            if (sscanf (string + nread_symb, ":%d %n", &read_label, add_nread) != 1)
            {
                printf ("Wrong argument \'%s\' of jmp function in \'%s\' line\n", string + nread_symb, string);
                return -1;
            }
        }
        
        if (read_label != LABEL_POISON)
        {
            where_to_jump = find_label (labels, read_label);
            if (compile_number != 0 && where_to_jump == LABEL_POISON)
            {
                printf ("Label error: label %d wasn't found\n", read_label);
                return -1;
            }
            //printf ("where_to_jump after find_label %d\n", where_to_jump);
        }
        *val = where_to_jump;
        
        return 0;
    }
    else
    {
        printf ("Wrong jmp command in string \'%s\' \n", string);
        return -1;
    }
}
