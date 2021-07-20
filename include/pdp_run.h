#pragma once

#include <stdint.h>  // Required to uint32_t type


// HAS some argument in func
#define NO_PARAM 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8
#define HAS_XX 16
// Statuses for external device's registers
#define STATUS_READY 0200
#define STATUS_BUSY 0


typedef struct {
  word adr;
  word val;
} Arg;      // Type of data for dd, ss
typedef struct {
  Arg dd;
  Arg ss;
  unsigned char r;
  unsigned char nn;
  char xx;
  word is_byte_cmd;
} Param;    // Arguments for functions in structure
typedef struct {
  word mask;
  word opcode;
  char * name;
  char params;                // 000(XX)(R)(N)(SS)(DD) - 8 bits
  void (* do_func)(Param p);
} Command;  // Description for commands of PDP-11
typedef struct {
  adress ostat;
  adress odata;
}EDReg;  //External Device's Register


extern EDReg DisplayReg;  // External device's register for Display


// Modes
void mode0(Arg * res, int r, word is_byte_cmd);
void mode1(Arg * res, int r, word is_byte_cmd);
void mode2(Arg * res, int r, word is_byte_cmd);
void mode3(Arg * res, int r, word is_byte_cmd);
void mode4(Arg * res, int r, word is_byte_cmd);
void mode5(Arg * res, int r, word is_byte_cmd);
void mode6(Arg * res, int r, word is_byte_cmd);
void mode7(Arg * res, int r, word is_byte_cmd);

Arg get_mode(word w, word is_byte_cmd);                // Mode definition
Param get_params(word w, char params);  // Determines parameters for operations PDP-11

// Determines if the result of executing an assembler
// Instruction is negative
void set_N(uint32_t value, word is_byte_cmd);

// Determines if the result of executing an assembler
// Instruction is zero
void set_Z(uint32_t value);

// Determines if summed two positive numbers,
// and the result is negative
void set_V(uint32_t flag);

// Determines if there was an overflow
void set_C(uint32_t value, word is_byte_cmd);

word is_negative(uint32_t value, word is_byte_cmd);
