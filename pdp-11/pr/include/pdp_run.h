#pragma once

// Наличие аргументов в функции
#define NO_PARAM 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8
#define HAS_XX 16

typedef struct {
  word adr;
  word val;
} Arg;      // Тип данных для dd, ss
typedef struct {
  Arg dd;
  Arg ss;
  unsigned char r;
  unsigned char nn;
  word is_byte_cmd;
} Param;    // Аргументы для функций в одной структуре
typedef struct {
  word mask;
  word opcode;
  char * name;
  char params;                // 000(XX)(R)(N)(SS)(DD) - 8 бит
  void (* do_func)(Param p);
} Command;  // Описание для команд PDP-11

// Моды
void mode0(Arg * res, int r);
void mode1(Arg * res, int r);
void mode2(Arg * res, int r);
void mode3(Arg * res, int r);
void mode4(Arg * res, int r);
void mode5(Arg * res, int r);
void mode6(Arg * res, int r);
void mode7(Arg * res, int r);

Arg get_modereg(word w);                // Определение моды
Param get_params(word w, char params);  // Определение параметров для операций pdp11

// this function using global variable process_state_word
// it is defined at "pdp_main_func.h"
// two_bits_pattern looks like 0...0XX, where X is 1 or 0
void set_negative_and_zero_flags(byte two_bits_pattern); 
void set_carry_flag(byte one_bit_pattern);
void set_overflow_flag(byte one_bit_pattern); 
