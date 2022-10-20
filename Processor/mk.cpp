#include <sys/types.h>
#include <stdlib.h>

int main ()
{
    system ("cd Build; ./ASM.exe ../Text_File.txt; ./CPU.exe ../b.bin");
}
