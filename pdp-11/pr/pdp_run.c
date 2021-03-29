#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

word reg[8];

#define pc reg[7]

Command cmd[] = {
    //{0170000, 0010000, "mov", do_mov},
    {0177777, 0000000, "halt", do_halt}
};
    

void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        logger(TRACE, "%06o %06o\n", pc, w);
        pc += 2;
        
        if(w == 0)
        {
            logger(TRACE, "halt \n");
            do_halt();
        }
        else
        {
            printf("smth wrong\n");
            exit(1);
        }
        /* else if((w & 0xF000) == 0010000)   //01SSDD
        {
            logger(TRACE, "mov ");
            do_mov();
        } */
    }
}
