#include <stdio.h>
#include <string.h>
#include <fcntl.h> /*read/write flags*/
#include <sys/types.h> /*types definitions*/
#include <sys/stat.h> /*the struct which stat returns*/
#include "Oneguine_functions.h"

size_t fsize (char* name)
{
    struct stat stbuf;
    if (stat (name, &stbuf) == -1)
    {
        printf ("Error: can't get information about %s file\n", name);
        return 0;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    {
        printf ("Error: this is the directory!\n");
        return 0;
    }
    
    return stbuf.st_size;
}
