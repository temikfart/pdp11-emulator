#include <stdio.h>
#include <stdarg.h>
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
void process_state_word_print() {
  logger(INFO, 
         "N = %1o Z = %1o V = %1o C = %1o \n",
         (process_state_word & 15) >> 3,  // NZVC -> N
         (process_state_word & 7) >> 2,  // NZVC -> Z
         (process_state_word & 3) >> 1,  // NZVC -> V
         process_state_word & 1  // NZVC -> C
         ); 
}
