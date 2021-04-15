#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pdp.h"
#include "pdp_run.h"
#include "pdp_add_func.h"
#include "pdp_main_func.h"

void do_halt(Param p) {
  logger(INFO, 
         "\n-----------------HALT------------------\n");
  result_print(); 
  exit(0);
}

void do_mov(Param p) {
  logger(DEBUG, "\nR%o = %06o.\n", p.dd.adr, p.ss.val);

  if (p.is_byte_cmd) {
    b_write(p.dd.adr, p.ss.val);
  } else {
    w_write(p.dd.adr, p.ss.val);
  }

  // NZVC == **0-
  set_NZ(p.ss.val, p.is_byte_cmd);
}

void do_add(Param p) {
  logger(DEBUG, "\nR%o = R%o + R%o.\n", p.dd.adr, p.dd.adr, p.ss.adr);
  
  uint32_t w = w_read(p.dd.adr);
  w = w + p.ss.val;
  w_write(p.dd.adr, w);

  // NZVC == ****
  set_NZ(w, p.is_byte_cmd);
  set_C(w, p.is_byte_cmd);
}

void do_sob(Param p) {
  reg[p.r]--;
  if (reg[p.r] != 0) {
    pc = pc - 2*p.nn;
  }

  // NZVC == ----

  logger(DEBUG, "\nR%o = %o, PC = %o.\n", p.r, reg[p.r], pc);
}

void do_clr(Param p) {
  logger(DEBUG, "\nmem[%o] = 0.\n", p.dd.adr);
  
  w_write(p.dd.adr, 0);

  // NZVC == 0100
  set_NZ(0, p.is_byte_cmd);
  set_C(0, p.is_byte_cmd);
}

void do_nothing(Param p) {
  return;
}

void do_unknown(Param p) {
  logger(ERROR, "unknown\n");
  
  exit(1);
}

// changing N, Z flags to some values and set V, C flags to 0
void do_tst(Param p) {
  byte zero_b = 0;

  // p.dd.val -- it is the value for which we set flags N, Z flags
  word tested_value = p.dd.val;
  
  // NZVC == **00
	set_NZ(tested_value, p.is_byte_cmd);
	set_C(0, p.is_byte_cmd);

	logger(DEBUG, "\nvalue: %o NZVC = %1o%1o0%o\n",
         tested_value, psw.N, psw.Z, psw.C);
}

void do_cmp(Param p) {
  word left_value = p.ss.val;
  word right_value = p.dd.val;

  uint32_t tested_value = left_value - right_value;
  

  // NZVC == ****
  set_NZ(tested_value, p.is_byte_cmd);
  set_C(tested_value, p.is_byte_cmd);

  logger(DEBUG, "\nvalue: %o NZVC = %1o%1o0%o\n",
         tested_value, psw.N, psw.Z, psw.C);
}
