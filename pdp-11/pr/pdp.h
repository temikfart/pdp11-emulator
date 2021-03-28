#pragma once

#define MEMSIZE (64*1024)

#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3
#define SILENT -1

typedef unsigned char byte;         //8 bit
typedef unsigned short int word;    //16 bit
typedef word Adress;                //16 bit

extern byte mem[MEMSIZE];
extern int current_log_lvl;

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void mem_dump(Adress start, word n);
void load_file();

void logger(int log_lvl, const char * format, ...);

void test_mem();
void test_odd_adr();