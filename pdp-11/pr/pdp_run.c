#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

#define pc reg[7]

static Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "unknown", do_unknown}
};
    

void run()
{
    pc = 01000;
    while(1)
    {
        logger(DEBUG, "run-func running\n");
        
        word w = w_read(pc);
        logger(TRACE, "%06o %06o: ", pc, w);
        pc += 2;
        int i = 0;
        
        while(1)
        {
            if((cmd[i]).mask == 0 && (cmd[i]).opcode == 0)
            {
                (cmd[i]).do_func();
                break;
            }
            if((w & (cmd[i]).mask) == (cmd[i]).opcode)
            {
                logger(TRACE, "%s\n", (cmd[i]).name);
                (cmd[i]).do_func();
                break;
            }
            i++;
        }
    }
}
