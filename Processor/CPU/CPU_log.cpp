#include <stdio.h>

void binary_out (int cmd);

void cmd_dump (int cmd)
{
    printf ("%d(%x)", cmd, cmd);
    binary_out (cmd);
    printf ("(%s %s %s, #%d)\n", (cmd & 0x80)? "M" : "m", (cmd & 0x40)? "R" : "r", (cmd & 0x20)? "I" : "i", cmd & 0x1F);
}

void binary_out (int cmd)
{
    for (int i = 0; i < 8; i++) {
        printf("%c", (cmd & 0x80) ? '1' : '0');
        cmd <<= 1;
    }
}
