#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"
#include "pdp_run.h"

static Param p;                 //Структура для параметров функций cmd[]
word is_byte_cmd;      //1 - Byte функция, 0 - Word функция

//Массив всех команд
static Command cmd[] = {
    {0170000, 0060000, "add", HAS_DD | HAS_SS, do_add},
    {0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov},
    {0170000, 0110000, "movb", HAS_DD | HAS_SS, do_mov},
    {0177000, 0077000, "sob", HAS_R | HAS_N, do_sob},
    {0177700, 0005000, "clr", HAS_DD, do_clr},
    {0177777, 0000000, "halt", NO_PARAM, do_halt},
    {0000000, 0000000, "unknown", NO_PARAM, do_unknown}
};

Arg get_modereg(word w)
{
    Arg res;
    int r = w & 7;              //Номер регистра
    int mode = (w >> 3) & 7;    //Номер моды
    switch(mode)
    {
        case 0:             //Mode 0: Rn
            mode0(&res, r);
            break;
        case 1:             //Mode 1: (Rn)
            mode1(&res, r);
            break;
        case 2:             //Mode 2: (Rn)+
            mode2(&res, r);
            break;
        case 3:
            mode3(&res, r);
            break;
        case 4:             //Mode 4: -(Rn)
            mode4(&res, r);
            break;
        default:
            logger(ERROR, "Mode %o not implemented yet.\n", mode);
            exit(1);
    }
    
    return res;
}
Param get_params(word w, char params)
{
    logger(DEBUG, "\nget_params: word = %06o; params = %d.\n", w, params);
    
    Param res;
    
    if((params & HAS_SS) == HAS_SS)
        res.ss = get_modereg(w >> 6);
    
    if((params & HAS_DD) == HAS_DD)
        res.dd = get_modereg(w);
    
    if((params & HAS_R) == HAS_R)
    {
        res.r = (w >> 6) & 1;
        logger(TRACE, "R%o ", res.r);
    }
    
    if((params & HAS_N) == HAS_N)
    {
        res.nn = w & 077;
        logger(TRACE, "%o ", (pc - 2*res.nn));
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
        is_byte_cmd = (w >> 15) & 1;
        
        while(1)
        {
            if((w & (cmd[i]).mask) == (cmd[i]).opcode)
            {
                logger(TRACE, "%s ", (cmd[i]).name);
                
                p = get_params(w, (cmd[i]).params);
                (cmd[i]).do_func(p);
                break;
            }
            i++;
        }
        //DEBUG
        if(current_log_lvl > TRACE)
            reg_print();
    }
}
//============================================
//====================МОДЫ====================
//============================================
void mode0(Arg * res, int r)
{
    res->adr = r;
    res->val = reg[r];
    logger(TRACE, "R%o ", r);
}
void mode1(Arg * res, int r)
{
    res->adr = reg[r];
    if(is_byte_cmd)
        res->val = b_read(res->adr);
    else
        res->val = w_read(res->adr);
    
    logger(TRACE, "(R%o) ", r);
}
void mode2(Arg * res, int r)
{
    res->adr = reg[r];
    if(is_byte_cmd)
        res->val = b_read(res->adr);
    else
        res->val = w_read(res->adr);
    
    if(is_byte_cmd && r < 6)
        reg[r] += 1;
    else
        reg[r] += 2;
        
    if(r == 7)
        logger(TRACE, "#%o ", res->val);
    else
        logger(TRACE, "(R%o)+ ", r);
}
void mode3(Arg * res, int r)
{
    res->adr = w_read(reg[r]);
    res->val = w_read(res->adr);
    reg[r] += 2;
    
    logger(TRACE, "@#%o ", res->adr);
}
void mode4(Arg * res, int r)
{
    if(r == 7 && pc == 8)   //Это после появления PSW переделается
    {
        logger(FATAL, "Fatal error: Array index out of bounds.\n");
        exit(1);
    }
    
    if(is_byte_cmd && r < 6)
    {
        reg[r] -= 1;
        res->adr = reg[r];
        res->val = b_read(res->adr);
    }
    else
    {
        reg[r] -= 2;
        res->adr = reg[r];
        res->val = w_read(res->adr);
    }
    
    if(r == 7)
        logger(TRACE, "-(PC) ");
    else
        logger(TRACE, "-(R%o) ", r);
}
void mode5(Arg * res, int r);
void mode6(Arg * res, int r);
void mode7(Arg * res, int r);
