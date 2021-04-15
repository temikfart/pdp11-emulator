#pragma once

#include <stdint.h>  // required to uint32_t type

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

// determines if the result of executing an assembler 
// instruction is negative or zero 
void set_NZ(uint32_t value, word it_was_byte_cmd);

// determines if there was an overflow
void set_C(uint32_t value, word it_was_byte_cmd);

word it_is_negative(uint32_t value, word is_byte);