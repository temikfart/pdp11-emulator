#pragma once

#define CONSTANT_FOR_TURN_ON_C_FLAG 0x1ffff

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
void do_clc(Param p);

void do_scc(Param p);
void do_sen(Param p);
void do_sez(Param p);
void do_sec(Param p);

void do_br(Param p);
void do_bcc(Param p);
void do_bcs(Param p);
void do_beq(Param p);
void do_bpl(Param p);
