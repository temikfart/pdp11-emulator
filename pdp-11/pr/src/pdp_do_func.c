#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pdp.h"
#include "pdp_run.h"
#include "pdp_add_func.h"
#include "pdp_main_func.h"
#include "pdp_do_func.h"

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
  set_N(p.ss.val, p.is_byte_cmd);
  set_Z(p.ss.val, p.is_byte_cmd);
}

void do_add(Param p) {
  logger(DEBUG, "\nR%o = R%o + R%o.\n", p.dd.adr, p.dd.adr, p.ss.adr);
  
  uint32_t w = w_read(p.dd.adr);
  w = w + p.ss.val;
  w_write(p.dd.adr, w);

  // NZVC == ****
  set_N(w, p.is_byte_cmd);
  set_Z(w, p.is_byte_cmd);
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
  set_N(0, p.is_byte_cmd);
  set_Z(0, p.is_byte_cmd);
  set_C(0, p.is_byte_cmd);
}

void do_nop(Param p) {
  return;
}

void do_unknown(Param p) {
  logger(ERROR, "unknown\n");
  
  exit(1);
}

// changing N, Z flags to some values and set V, C flags to 0
void do_tst(Param p) {
  // p.dd.val -- it is the value for which we set flags N, Z flags
  word tested_value = p.dd.val;
  
  // NZVC == **00
	set_N(tested_value, p.is_byte_cmd);
	set_Z(tested_value, p.is_byte_cmd);
	set_C(0, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_cmp(Param p) {
	uint32_t tested_value;

	if (p.is_byte_cmd) {
		tested_value = (byte)(p.ss.val) - (byte)(p.dd.val);
	} else {
		tested_value = (word)p.ss.val - (word)p.dd.val;
	}

  // NZVC == ****
  set_N(tested_value, p.is_byte_cmd);
  set_Z(tested_value, p.is_byte_cmd);
  set_C(tested_value, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_ccc(Param p) {
  // NZVC == 0000
  set_N(1, p.is_byte_cmd);
  set_Z(1, p.is_byte_cmd);
  set_C(1, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_cln(Param p) {
	// NZVC == 0---
  set_N(1, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_clz(Param p) {
	// NZVC == -0--
  set_Z(1, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_clc(Param p) {
	// NZVC == ---0
  set_C(1, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_scc(Param p) {
  // NZVC == 1111
  set_N((byte)(-1), 1); 
  set_Z(0, p.is_byte_cmd);
  set_C(CONSTANT_FOR_TURN_ON_C_FLAG, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_sen(Param p) {
	// NZVC == 1---
  set_N((byte)(-1), 1);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_sez(Param p) {
	// NZVC == -1--
  set_Z(0, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}

void do_sec(Param p) {
	// NZVC == ---1
  set_C(CONSTANT_FOR_TURN_ON_C_FLAG, p.is_byte_cmd);

  logger(DEBUG, "\nNZVC = %1o%1o%1o%1o\n", psw.N, psw.Z, psw.V, psw.C);
}