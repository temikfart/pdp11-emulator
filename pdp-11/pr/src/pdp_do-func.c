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
    logger(DEBUG, "\nDebug: mo%s: R%o = %06o.\n", (is_byte_cmd) ? "vb" : "v", p.dd.adr, p.ss.val);
    
    if(is_byte_cmd)
        b_write(p.dd.adr, p.ss.val);
    else
        w_write(p.dd.adr, p.ss.val);
}
void do_add(Param p)
{
    logger(DEBUG, "\nDebug: add: R%o = R%o + R%o.\n", p.dd.adr, p.dd.adr, p.ss.adr);
    
    word w = w_read(p.dd.adr);
    w = w + p.ss.val;
    w_write(p.dd.adr, w);
}
void do_sob(Param p)
{
    reg[p.r]--;
    if(reg[p.r] != 0)
        pc = pc - 2*p.nn;
    
    logger(DEBUG, "\nDebug: sob: R%o = %o, PC = %o.\n", p.r, reg[p.r], pc);
}
void do_clr(Param p)
{
    logger(DEBUG, "\nDebug: clr: mem[%o] = 0.\n", p.dd.adr);
    
    w_write(p.dd.adr, 0);
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
