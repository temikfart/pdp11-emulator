#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

//Структура для параметров функций cmd[]
Param p;
//Массив всех команд
static Command cmd[] = {
    {0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov},
    {0170000, 0060000, "add", HAS_DD | HAS_SS, do_add},
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
        //Mode 4: -(Rn)
        case 4:
            if(r == 7 && pc == 0)
            {
                logger(FATAL, "Fatal error: Array index out of bounds.\n");
                exit(1);
            }
            reg[r] -= 2;                //-= 1 если операция байтовая
            res.adr = reg[r];
            res.val = w_read(res.adr);  //b_read если операция байтовая
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
Param get_params(word w, char params)
{
    logger(DEBUG, "\nget_params(word = %06o, params = %d) is running\n", w, params);
    
    Param res;
    
    if(params == NO_PARAM)
    {
        //logger(DEBUG, "No params\n");
        
        return res;
    }
    
    if((params & HAS_SS) == HAS_SS)
    {
        //logger(DEBUG, "\nhas a SS-parameter\n");
        res.ss = get_modereg(w >> 6);
    }
    if((params & HAS_DD) == HAS_DD)
    {
        //logger(DEBUG, "\nhas a DD-parameter\n");
        res.dd = get_modereg(w);
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
