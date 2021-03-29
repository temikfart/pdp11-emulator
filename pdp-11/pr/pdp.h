#pragma once

//Constants
#define MEMSIZE (64*1024)

#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3
#define SILENT -1
//====================

//Structures
typedef unsigned char byte;         //8 bit
typedef unsigned short int word;    //16 bit
typedef word Adress;                //16 bit
//====================

//Global variables
extern byte mem[MEMSIZE];
extern int current_log_lvl;
//====================

//pdp functions
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void mem_dump(Adress start, word n);
void load_file();
void console_arg(int argc, char * argv[]);
//====================

//Additional functions
void logger(int log_lvl, const char * format, ...);
//====================

//Tests
void test_mem_1(word w, byte b1, byte b0);
void test_mem();
void test_odd_adr();
void test_logger_prints();
void test_logger();
void test_console_arg();
//====================
