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
  // Set N, Z, V flags with agreement with (SS - DD) [word]
  {0170000, 0020000, "cmp", HAS_DD | HAS_SS, do_cmp},
  // Set N, Z, V flags with agreement with (SS - DD) [byte]
  {0170000, 0120000, "cmpb", HAS_DD | HAS_SS, do_cmp},
  // Subtract One and Branch: PC=PC-2*NN
  {0177000, 0077000, "sob", HAS_R | HAS_N, do_sob},
  
  // DD = 0
  {0177700, 0005000, "clr", HAS_DD, do_clr},
  // Set N, Z flags in agreement with DD [word]
  {0177700, 0005700, "tst", HAS_DD, do_tst},
  // Set N, Z flags in agreement with DD [byte]
  {0177700, 0105700, "tstb", HAS_DD, do_tst},

  // Clear all condition codes NZVC = 0000
  {0177777, 0000257, "ccc", NO_PARAM, do_ccc},
  // Clear N flag
  {0177777, 0000250, "cln", NO_PARAM, do_cln},
  // Clear Z flag
  {0177777, 0000244, "clz", NO_PARAM, do_clz},
  // Clear V flag
  {0177777, 0000242, "clv", NO_PARAM, do_clv},
  // Clear C flag
  {0177777, 0000241, "clc", NO_PARAM, do_clc},

  // Set all condition codes at one NZVC = 1111
  {0177777, 0000277, "scc", NO_PARAM, do_scc},
  // Set N = 1
  {0177777, 0000270, "sen", NO_PARAM, do_sen},
  // Set Z = 1
  {0177777, 0000264, "sez", NO_PARAM, do_sez},
  // Set V = 1
  {0177777, 0000262, "sev", NO_PARAM, do_sev},
  // Set C = 1
  {0177777, 0000261, "sec", NO_PARAM, do_sec},

  // Branch (pc = pc + XX*2)
  {0177400, 0000400, "br", HAS_XX, do_br},
  // Branch if Carry Clear (C = 0)
  {0177400, 0103000, "bcc", HAS_XX, do_bcc},
  // Branch if Carry Set (C = 1)
  {0177400, 0103400, "bcs", HAS_XX, do_bcs},
  // Branch if EQual (Z = 0)
  {0177400, 0001400, "beq", HAS_XX, do_beq},
  // Branch if Greater or Equal (N and V = 0)
  {0177400, 0002000, "bge", HAS_XX, do_bge},
  // Branch if Greater Than (Z or {N and V} = 0)
  {0177400, 0003000, "bgt", HAS_XX, do_bgt},
  // Branch if HIgher (C and Z = 0)
  {0177400, 0101000, "bhi", HAS_XX, do_bhi},
  // Branch if Less or Equal (Z or {N and V} = 1)
  {0177400, 0003400, "ble", HAS_XX, do_ble},
  // Branch if Less Than (N and V = 1)
  {0177400, 0002400, "blt", HAS_XX, do_blt},
  // Branch if Lower Or Same (C and Z = 1)
  {0177400, 0101400, "blos", HAS_XX, do_blos},
  // Branch if MInus
  {0177400, 0100400, "bmi", HAS_XX, do_bmi},
  // Branch if Not Equal
  {0177400, 0001000, "bne", HAS_XX, do_bne},
  // Branch if PLus (N = 0)
  {0177400, 0100000, "bpl", HAS_XX, do_bpl},
  // Branch if oVerflow clear (V = 0)
  {0177400, 0102000, "bvc", HAS_XX, do_bvc},
  // Branch if oVerflow set (V = 1)
  {0177400, 0102400, "bvs", HAS_XX, do_bvs},

  // Stop program execution
  {0177777, 0000000, "halt", NO_PARAM, do_halt},  
  // No OPeration
  {0177777, 0000240, "nop", NO_PARAM, do_nop},

  // Buffer element
  {0000000, 0000000, "unknown", NO_PARAM, do_unknown}
};

Arg get_mode(word w, word is_byte_cmd) {
  Arg res;
  int r = w & 7;        // Номер регистра
  int mode = (w >> 3) & 7;  // Номер моды
  
  switch (mode) {
    case 0:       // Mode 0: Rn
      mode0(&res, r, is_byte_cmd);
      break;
    case 1:       // Mode 1: (Rn)
      mode1(&res, r, is_byte_cmd);
      break;
    case 2:       // Mode 2: (Rn)+
      mode2(&res, r, is_byte_cmd);
      break;
    case 3:       // Mode 3: @(Rn)+
      mode3(&res, r, is_byte_cmd);
      break;
    case 4:       // Mode 4: -(Rn)
      mode4(&res, r, is_byte_cmd);
      break;
    default:
      logger(ERROR, "Mode %o not implemented yet.\n", mode);
      exit(1);
  }
  
  return res;
}
Param get_params(word w, char params) {
//  logger(DEBUG, "params = %d ", params);

  // Индикатор режима do-функции в функции run.
  // 1 - Byte функция, 0 - Word функция
  word is_byte_cmd = (w >> 15) & 1;

  Param res;
  
  // SS
  if ((params & HAS_SS) == HAS_SS) {
    res.ss = get_mode(w >> 6, is_byte_cmd);
  }
  // DD
  if ((params & HAS_DD) == HAS_DD) {
    res.dd = get_mode(w, is_byte_cmd);
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
  // XX
  if ((params & HAS_XX) == HAS_XX) {
    res.xx = w & 0xFF;
  }
  // is_byte_cmd
  res.is_byte_cmd = is_byte_cmd;
  
  return res;
}
void run() {
  // Default preset
  pc = 01000;
  w_write(DisplayReg.ostat, STATUS_READY);
  edr_print();

  logger(INFO, "\n----------------RUNNING----------------\n");

  while (1) {
    word w = w_read(pc);
    logger(TRACE, "\n%06o %06o: ", pc, w);

    // Registers protection
    if (pc < 8) {
      logger(FATAL, "Fatal error: Array index out of bounds.\n");
      exit(1);
    } else {
      pc += 2;
    }

    int i = 0;
    
    while (1) {
      if ((w & (cmd[i]).mask) == (cmd[i]).opcode) {
        logger(TRACE, "%-8s", (cmd[i]).name);

        p = get_params(w, (cmd[i]).params);
        (cmd[i]).do_func(p);

        // DEBUG
        if (current_log_lvl > TRACE) {
          reg_print();
        }
        psw_log_print(DEBUG);
        break;
      }
      i++;
    }
  }
}
/*==========================================
====================MODES===================
==========================================*/
void mode0(Arg *res, int r, word is_byte_cmd) {
  // Action
  res->adr = r;
  res->val = reg[r];

  // Print
  logger(TRACE, "R%o ", r);
}
void mode1(Arg *res, int r, word is_byte_cmd) {
  // Action
  res->adr = reg[r];
  if (is_byte_cmd) {
    res->val = b_read(res->adr);
  } else {
    res->val = w_read(res->adr);
  }

  // Print
  logger(TRACE, "(R%o) ", r);
}
void mode2(Arg *res, int r, word is_byte_cmd) {
  // Action
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

  // Print
  if (r == 7) {
    logger(TRACE, "#%o ", res->val);
  } else {
    logger(TRACE, "(R%o)+ ", r);
  }
}
void mode3(Arg *res, int r, word is_byte_cmd) {
  // Action
  res->adr = w_read(reg[r]);
  res->val = w_read(res->adr);
  reg[r] += 2;

  // Print
  logger(TRACE, "@#%o ", res->adr);
}
void mode4(Arg *res, int r, word is_byte_cmd) {
  // Action
  if (is_byte_cmd && r < 6) {
    reg[r] -= 1;
    res->adr = reg[r];
    res->val = b_read(res->adr);
  } else {
    reg[r] -= 2;
    res->adr = reg[r];
    res->val = w_read(res->adr);
  }

  // Print
  switch (r) {
    case 6:
      logger(TRACE, "-(SP) ");
      break;
    case 7:
      logger(TRACE, "-(PC) ");
      break;
    default:
      logger(TRACE, "-(R%o) ", r);
      break;
  }
}
void mode5(Arg *res, int r, word is_byte_cmd);
void mode6(Arg *res, int r, word is_byte_cmd);
void mode7(Arg *res, int r, word is_byte_cmd);

word is_negative(uint32_t value, word is_byte_cmd) {
  return value >> (is_byte_cmd ? 7 : 15) & 1;
}

void set_N(uint32_t value, word is_byte_cmd) {
  psw.N = (char)is_negative(value, is_byte_cmd);
}

void set_Z(uint32_t value) {
  psw.Z = (char)(value == 0);
}

void set_V(uint32_t flag) {
  switch (flag) {
    case PSW_V_OFF:
      psw.V = 0;
      break;
    case PSW_V_ON:
      psw.V = 1;
      break;
    case PSW_V_DEFAULT:
      psw.V = (char)(psw.N ^ psw.C);
      break;
    default:
      break;
  }
}

void set_C(uint32_t value, word is_byte_cmd) {
  psw.C = (char)((value >> (is_byte_cmd ? 8 : 16)) & 1);
}
