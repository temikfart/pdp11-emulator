#pragma once

//Постоянные
#define MEMSIZE (64*1024)   //Размер памяти PDP-11
#define pc reg[7]           //Program Counter

//Уровни логирования
#define FATAL 0
#define ERROR 1
#define INFO 2
#define TRACE 3
#define DEBUG 4
#define SILENT -1
//====================

//Структуры
typedef unsigned char byte;         // 8 бит
typedef unsigned short int word;    //16 бит
typedef word Adress;                //16 бит
//====================

//Глобальные переменные
extern byte mem[MEMSIZE];           //Память
extern int current_log_lvl;         //Уровень логирования
extern word reg[8];                 //Регистры R0, ..., R8
//====================

//PDP main-функции
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void mem_dump(Adress start, word n);
void load_file();
void console_arg(int argc, char * argv[]);
void run();
//====================

//Additional functions
void logger(int log_lvl, const char * format, ...);
void reg_print();
//====================

//Tests
void test_mem();
void test_odd_adr();
void test_logger_prints();
void test_logger();
void test_console_arg();
//====================
