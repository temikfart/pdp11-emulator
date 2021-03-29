#pragma once

//Constants
#define MEMSIZE (64*1024)

#define FATAL 0
#define ERROR 1
#define INFO 2
#define TRACE 3
#define DEBUG 4
#define SILENT -1
//====================

//Structures
typedef unsigned char byte;         //8 bit
typedef unsigned short int word;    //16 bit
typedef word Adress;                //16 bit
typedef struct
{
    word mask;
    word opcode;
    char * name;
    void (* do_func)(void);
}Command;                           //Описание для команд PDP-11
//====================

//Global variables
extern byte mem[MEMSIZE];       //Память
extern int current_log_lvl;     //Уровень логирования
extern word reg[8];             //Регистры R0, ..., R8
//====================

//PDP main-functions
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void mem_dump(Adress start, word n);
void load_file();
void console_arg(int argc, char * argv[]);
void run();
//====================

//PDP do-functions
void do_halt();
void do_mov();
void do_add();
void do_nothing();
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
