#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

void do_halt(Arg dd, Arg ss)
{
    logger(INFO, "\n-----------------HALT------------------\n");
    logger(INFO, 
        "R0=%06o R2=%06o R4=%06o SP=%06o\n", 
        reg[0], reg[2], reg[4], reg[6]);
    logger(INFO, 
        "R1=%06o R3=%06o R5=%06o PC=%06o\n", 
        reg[1], reg[3], reg[5], reg[7]);
    exit(0);
}
void do_mov(Arg dd, Arg ss)
{
    logger(DEBUG, "\nDebug: mov: R%o = %06o.\n", dd.adr, ss.val);
    w_write(dd.adr, ss.val);
}
void do_add(Arg dd, Arg ss)
{
    logger(DEBUG, "\nDebug: add: R%o = R%o + R%o.\n", dd.adr, dd.adr, ss.adr);
    word w = w_read(dd.adr);
    w = w + ss.val;
    w_write(dd.adr, w);
}
void do_nothing(Arg dd, Arg ss)
{
    return;
}
void do_unknown(Arg dd, Arg ss)
{
    logger(ERROR, "unknown\n");
}
