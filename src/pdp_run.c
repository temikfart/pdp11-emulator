#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pdp.h"
#include "pdp_run.h"
#include "pdp_do_func.h"
#include "pdp_add_func.h"
#include "pdp_main_func.h"

// Структура для параметров функций cmd[]
static Param p;
// Индикатор режима do-функции в функции run.
// 1 - Byte функция, 0 - Word функция
static word is_byte_cmd;
// Display's external device's register
EDReg DisplayReg = {0177564, 0177566};

// Массив всех команд
static Command cmd[] = {
  // DD = SS + DD
  {0170000, 0060000, "add", HAS_DD | HAS_SS, do_add},
  // DD = SS [word]
  {0170000, 0010000, "mov", HAS_DD | HAS_SS, do_mov},
  // DD = SS [byte]
  {0170000, 0110000, "movb", HAS_DD | HAS_SS, do_mov},
  // set N, Z, V flags with agreement with (SS - DD) [word]
  {0170000, 0020000, "cmp", HAS_DD | HAS_SS, do_cmp},
  // set N, Z, V flags with agreement with (SS - DD) [byte]
  {0170000, 0120000, "cmpb", HAS_DD | HAS_SS, do_cmp},
  // Subtract One and Branch: PC=PC-2*NN
  {0177000, 0077000, "sob", HAS_R | HAS_N, do_sob},
  
  // DD = 0
  {0177700, 0005000, "clr", HAS_DD, do_clr},
  // set N, Z flags in agreement with DD [word]
  {0177700, 0005700, "tst", HAS_DD, do_tst},
  // set N, Z flags in agreement with DD [byte]
  {0177700, 0105700, "tstb", HAS_DD, do_tst},

  // clear all condition codes NZVC = 0000
  {0177777, 0000257, "ccc", NO_PARAM, do_ccc},
  // clear N flag
  {0177777, 0000250, "cln", NO_PARAM, do_cln},
  // clear Z flag
  {0177777, 0000244, "clz", NO_PARAM, do_clz},
  // clear C flag
  {0177777, 0000241, "clc", NO_PARAM, do_clc},

  // set all condition codes at one NZVC = 1111
  {0177777, 0000277, "scc", NO_PARAM, do_scc},
  // set N = 1
  {0177777, 0000270, "sen", NO_PARAM, do_sen},
  // set Z = 1
  {0177777, 0000264, "sez", NO_PARAM, do_sez},
  // set C = 1
  {0177777, 0000261, "sec", NO_PARAM, do_sec},

  // check flag Z (if Z = 0)
  {0177700, 0001400, "beq", HAS_XX, do_beq},
  // check flag N (if N = 0)
  {0177700, 0100000, "bpl", HAS_XX, do_bpl},

  // stop program execution
  {0177777, 0000000, "halt", NO_PARAM, do_halt},  
  // no operation
  {0177777, 0000240, "nop", NO_PARAM, do_nop},

  // buffer element
  {0000000, 0000000, "unknown", NO_PARAM, do_unknown}
};

Arg get_modereg(word w) {
  Arg res;
  int r = w & 7;        // Номер регистра
  int mode = (w >> 3) & 7;  // Номер моды
  
  switch (mode) {
    case 0:       // Mode 0: Rn
      mode0(&res, r);
      break;
    case 1:       // Mode 1: (Rn)
      mode1(&res, r);
      break;
    case 2:       // Mode 2: (Rn)+
      mode2(&res, r);
      break;
    case 3:
      mode3(&res, r);
      break;
    case 4:       // Mode 4: -(Rn)
      mode4(&res, r);
      break;
    default:
      logger(ERROR, "Mode %o not implemented yet.\n", mode);
      exit(1);
  }
  
  return res;
}
Param get_params(word w, char params) {
  logger(DEBUG, "params = %d ", params);
  
  Param res;
  
  // SS
  if ((params & HAS_SS) == HAS_SS) {
    res.ss = get_modereg(w >> 6);
  }
  // DD
  if ((params & HAS_DD) == HAS_DD) {
    res.dd = get_modereg(w);
  }
  // R
  if ((params & HAS_R) == HAS_R) {
    res.r = (w >> 6) & 1;
    logger(TRACE, "R%o ", res.r);
  }
  // NN
  if ((params & HAS_N) == HAS_N) {
    res.nn = w & 077;
    logger(TRACE, "%o ", (pc - 2*res.nn));
  }
  // is_byte_cmd
  res.is_byte_cmd = (w >> 15) & 1;
  
  return res;
}
void run() {
  // Default preset
  pc = 01000;
  w_write(DisplayReg.ostat, STATUS_READY);
//  w_write(DisplayReg.odata, STATUS_BUSY);
  edr_print();

  logger(INFO, "\n----------------RUNNING----------------");

  while (1) {
    word w = w_read(pc);
    logger(TRACE, "\n%06o %06o: ", pc, w);
    pc += 2;
    
    int i = 0;
    is_byte_cmd = (w >> 15) & 1;
    
    while (1) {
      if ((w & (cmd[i]).mask) == (cmd[i]).opcode) {
        logger(TRACE, "%s ", (cmd[i]).name);

        p = get_params(w, (cmd[i]).params);
        (cmd[i]).do_func(p);
        
        psw_log_print(TRACE);
        break;
      }
      i++;
    }
    // DEBUG
    if (current_log_lvl > TRACE) {
      reg_print();
    }
  }
}
// ============================================
// ====================МОДЫ====================
// ============================================
void mode0(Arg *res, int r) {
  res->adr = r;
  res->val = reg[r];
  logger(TRACE, "R%o ", r);
}
void mode1(Arg *res, int r) {
  res->adr = reg[r];
  if (is_byte_cmd) {
    res->val = b_read(res->adr);
  } else {
    res->val = w_read(res->adr);
  }
  
  logger(TRACE, "(R%o) ", r);
}
void mode2(Arg *res, int r) {
  res->adr = reg[r];
  if (is_byte_cmd) {
    res->val = b_read(res->adr);
  } else {
    res->val = w_read(res->adr);
  }
  
  if (is_byte_cmd && r < 6) {
    reg[r] += 1;
  } else {
    reg[r] += 2;
  }
    
  if (r == 7) {
    logger(TRACE, "#%o ", res->val);
  } else {
    logger(TRACE, "(R%o)+ ", r);
  }
}
void mode3(Arg *res, int r) {
  res->adr = w_read(reg[r]);
  res->val = w_read(res->adr);
  reg[r] += 2;
  
  logger(TRACE, "@#%o ", res->adr);
}
void mode4(Arg *res, int r) {
  if (r == 7 && pc == 8) {  // Это после появления PSW переделается
    logger(FATAL, "Fatal error: Array index out of bounds.\n");
    exit(1);
  }
  
  if (is_byte_cmd && r < 6) {
    reg[r] -= 1;
    res->adr = reg[r];
    res->val = b_read(res->adr);
  } else {
    reg[r] -= 2;
    res->adr = reg[r];
    res->val = w_read(res->adr);
  }
  
  if (r == 7) {
    logger(TRACE, "-(PC) ");
  } else {
    logger(TRACE, "-(R%o) ", r);
  }
}
void mode5(Arg *res, int r);
void mode6(Arg *res, int r);
void mode7(Arg *res, int r);

word is_negative(uint32_t value, word is_byte_cmd) {
  return is_byte_cmd ? (value >> 7) & 1 : (value >> 15) & 1;
}

void set_N(uint32_t value, word is_byte_cmd) {
  psw.N = is_negative(value, is_byte_cmd);
}

void set_Z(uint32_t value, word is_byte_cmd) {
  psw.Z = (value == 0);
}

void set_C(uint32_t value, word is_byte_cmd) {
  psw.C = (value >> (is_byte_cmd ? 8 : 16)) & 1;
}

