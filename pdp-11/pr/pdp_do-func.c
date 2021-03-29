#include <stdio.h>
#include <stdlib.h>
#include "pdp.h"

void do_halt()
{
    logger(TRACE, "The end\n");
    exit(0);
}
/* void do_mov()
{
    
}
void do_add()
{}
void do_nothing()
{} */