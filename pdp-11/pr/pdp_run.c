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
Arg ss, dd;    

Arg get_modereg(word w)
{
    Arg res;
    int r = w & 7;              //Номер регистра
    int mode = (w >> 3) & 7;    //Номер моды
    switch(mode)
    {
        //Mode 0: Rn
        case 0:
            res.adr = r;
            res.val = reg[r];
            logger(TRACE, "R%o ", r);
            break;
        //Mode 1: (Rn)
        case 1:
            res.adr = reg[r];
            res.val = w_read(res.adr);  //b_read если операция байтовая
            logger(TRACE, "(R%o) ", r);
            break;
        //Mode 2: (Rn)+
        case 2:
            res.adr = reg[r];
            res.val = w_read(res.adr);  //b_read если операция байтовая
            reg[r] += 2;                //+= 1 если операция байтовая
            if(r == 7)
                logger(TRACE, "#%o ", res.val);
            else
                logger(TRACE, "(R%o)+ ", r);
            break;
        default:
            logger(ERROR, "Mode %o not implemented yet.\n", r);
            exit(1);
    }
    
    return res;
}
void run()
{
   logger(INFO, "\n----------------RUNNING----------------");
    pc = 01000;
    while(1)
    {
        
        word w = w_read(pc);
        logger(TRACE, "\n%06o %06o: ", pc, w);
        pc += 2;
        int i = 0;
        
        while(1)
        {
            //Unknown command
            if((cmd[i]).mask == 0 && (cmd[i]).opcode == 0)
            {
                logger(TRACE, "%s \n", (cmd[i]).name);
                (cmd[i]).do_func(dd, ss);
                break;
            }
            
            //Operation
            if((w & (cmd[i]).mask) == (cmd[i]).opcode)
            {
                logger(TRACE, "%s ", (cmd[i]).name);
                if((cmd[i]).opcode != 0)
                {
                    ss = get_modereg(w >> 6);
                    dd = get_modereg(w);
                }
                (cmd[i]).do_func(dd, ss);
                break;
            }
            i++;
        }
    }
}
