#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"
#include "pdp_run.h"

void do_halt(Param p)
{
    logger(INFO, 
        "\n-----------------HALT------------------\n");
    reg_print();
    
    exit(0);
}
void do_mov(Param p)
{
    logger(DEBUG, "\nDebug: mov: R%o = %06o.\n", p.dd.adr, p.ss.val);
    
    w_write(p.dd.adr, p.ss.val);
}
void do_add(Param p)
{
    logger(DEBUG, "\nDebug: add: R%o = R%o + R%o.\n", p.dd.adr, p.dd.adr, p.ss.adr);
    
    word w = w_read(p.dd.adr);
    w = w + p.ss.val;
    w_write(p.dd.adr, w);
}
void do_SOB(Param p)
{
    
}
void do_nothing(Param p)
{
    return;
}
void do_unknown(Param p)
{
    logger(ERROR, "unknown\n");
    
    exit(1);
}
