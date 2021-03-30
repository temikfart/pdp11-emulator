#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

void do_halt()
{
    logger(DEBUG, "The end\n");
    exit(0);
}
void do_mov()
{
    logger(DEBUG, "mov\n");
}
void do_add()
{
    logger(DEBUG, "add\n");
}
void do_nothing()
{
    return;
}
void do_unknown()
{
    logger(ERROR, "unknown\n");
}
