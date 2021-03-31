#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

void mode0(Arg * res, int r)
{
    res->adr = r;
    res->val = reg[r];
    logger(TRACE, "R%o ", r);
}
void mode1(Arg * res, int r)
{
    res->adr = reg[r];
    res->val = w_read(res->adr);  //b_read если операция байтовая
    logger(TRACE, "(R%o) ", r);
}
void mode2(Arg * res, int r)
{
    res->adr = reg[r];
    res->val = w_read(res->adr);  //b_read если операция байтовая
    reg[r] += 2;                //+= 1 если операция байтовая
    if(r == 7)
        logger(TRACE, "#%o ", res->val);
    else
        logger(TRACE, "(R%o)+ ", r);
}
void mode3(Arg * res, int r);
void mode4(Arg * res, int r)
{
    if(r == 7 && pc == 8)   //Это после появления PSW переделается
    {
        logger(FATAL, "Fatal error: Array index out of bounds.\n");
        exit(1);
    }
    reg[r] -= 2;                //-= 1 если операция байтовая
    res->adr = reg[r];
    res->val = w_read(res->adr);  //b_read если операция байтовая
    if(r == 7)
        logger(TRACE, "-(PC) ");
    else
        logger(TRACE, "-(R%o) ", r);
}
void mode5(Arg * res, int r);
void mode6(Arg * res, int r);
void mode7(Arg * res, int r);

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
