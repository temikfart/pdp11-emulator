#include <stdio.h>
#include <stdarg.h>
#include "pdp.h"

int current_log_lvl = INFO;

void logger(int log_lvl, const char * format, ...)
{
    if(log_lvl > current_log_lvl)
        return;
    va_list ptr;
    va_start(ptr, format);
    vprintf(format, ptr);
    va_end(ptr);
}