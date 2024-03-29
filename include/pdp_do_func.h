#pragma once

#define PSW_C_ON 0x1FFFF
#define PSW_V_OFF 0
#define PSW_V_ON 1
#define PSW_V_DEFAULT 2

void do_halt(Param p);
void do_mov(Param p);
void do_add(Param p);
void do_sob(Param p);
void do_clr(Param p);
void do_nop(Param p);
void do_unknown(Param p);

void do_tst(Param p);
void do_cmp(Param p);

void do_ccc(Param p);
void do_cln(Param p);
void do_clz(Param p);
void do_clv(Param p);
void do_clc(Param p);

void do_scc(Param p);
void do_sen(Param p);
void do_sez(Param p);
void do_sev(Param p);
void do_sec(Param p);

void do_br(Param p);
void do_bcc(Param p);
void do_bcs(Param p);
void do_beq(Param p);
void do_bge(Param p);
void do_bgt(Param p);
void do_bhi(Param p);
void do_ble(Param p);
void do_blt(Param p);
void do_blos(Param p);
void do_bmi(Param p);
void do_bne(Param p);
void do_bpl(Param p);
void do_bvc(Param p);
void do_bvs(Param p);
