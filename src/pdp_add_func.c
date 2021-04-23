#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "pdp.h"
#include "pdp_main_func.h"

void logger(int log_lvl, const char * format, ...) {
  if (log_lvl > current_log_lvl) {
    return;
  }
  va_list ptr;
  va_start(ptr, format);
  vprintf(format, ptr);
  va_end(ptr);
}

void reg_print() {
  logger(INFO, 
         "R0=%06o R2=%06o R4=%06o SP=%06o\
         \nR1=%06o R3=%06o R5=%06o PC=%06o\n", 
         reg[0], reg[2], reg[4], reg[6],
         reg[1], reg[3], reg[5], reg[7]);
}

void psw_log_print(uint8_t logging_level) {
  logger(logging_level, psw.N ? "[N" : "[-");
  logger(logging_level, psw.Z ? "Z" : "-");
  logger(logging_level, psw.V ? "V" : "-");
  logger(logging_level, psw.C ? "C]" : "-]");
}

void result_print() {
  reg_print();
  psw_log_print(INFO);
  logger(INFO, "\n"); //temporarily
}
