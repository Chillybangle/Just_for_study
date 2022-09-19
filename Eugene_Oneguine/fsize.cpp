#include <stdio.h>
#include <string.h>
#include <fcntl.h> /*флажки чтения и записи*/
#include <sys/types.h> /*определения типов*/
#include <sys/stat.h> /*структура, возвращаемая stat*/
#include "Oneguine_functions.h"

size_t fsize (char* name)
{
    struct stat stbuf;
    if (stat (name, &stbuf) == -1)
    {
        printf ("Error: can't get information about %s file\n", name);
        return -1; // size_t, -1 is not in range
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    {
        printf ("Error: this is the directory!\n");
        return -1;
    }
    
    return stbuf.st_size;
}
