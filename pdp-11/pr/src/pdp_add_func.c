#include <stdio.h>
#include <stdarg.h>
#include <string.h>
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

void psw_print() {
  // create template for printing
  char result_print[] = "NZVC";

  // point at the beggining of the structure
  char* p_psw = &(psw.N);

  for (int i = 0; i < strlen(result_print); i++) {
    if (!*(p_psw + i)) {
      result_print[i] = '-';
    }
  }

  // print name of flag if it is 1 and print "-" if it is 0
  logger(INFO, "NZVC: %s", result_print);
}

void result_print() {
  reg_print();
  psw_print();
}
