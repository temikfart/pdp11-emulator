#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

static Param p;                 //Структура для параметров функций cmd[]

//Массив всех команд
static Command cmd[] = {
    {0170000, 0060000, "add", HAS_DD | HAS_SS, do_add},
    {0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov},
    {0177000, 0077777, "SOB", HAS_R | HAS_N, do_SOB},
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
    logger(DEBUG, "\nget_params(word = %06o, params = %d) is running\n", w, params);
    
    Param res;
    
    if((params & HAS_SS) == HAS_SS)
        res.ss = get_modereg(w >> 6);
    
    if((params & HAS_DD) == HAS_DD)
        res.dd = get_modereg(w);
    
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
