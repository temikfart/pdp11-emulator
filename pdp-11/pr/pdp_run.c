#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

word reg[8];

#define pc reg[7]

Command cmd[] = {
    //{0170000, 0010000, "mov", do_mov},
    {0177777, 0000000, "halt", do_halt},
    {0177777, 0177777, "unknown", do_nothing}
};
    

void run()
{
    int i;
    pc = 01000;
    while(1)
    {
        logger(DEBUG, "Run function running\n");
        
        word w = w_read(pc);
        logger(TRACE, "%06o %06o\n", pc, w);
        pc += 2;
        
        for(i = 0; (cmd[i]).opcode != 0177777; i++)
        {
            if((w & (cmd[i]).mask) == (cmd[i]).opcode)
            {
                logger(TRACE, "%s\n", (cmd[i]).name);
                (cmd[i]).do_func();
            }
        }
        if((cmd[i]).opcode == 0177777)
            logger(ERROR, "unknown\n");
    }
}
