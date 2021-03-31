#pragma once

//Constants
#define MEMSIZE (64*1024)   //Размер памяти PDP-11
#define pc reg[7]           //Program Counter

//Уровни логирования
#define FATAL 0
#define ERROR 1
#define INFO 2
#define TRACE 3
#define DEBUG 4
#define SILENT -1

//Наличие аргументов в функции
#define NO_PARAM 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8
#define HAS_XX 16
//====================

//Structures
typedef unsigned char byte;         // 8 бит
typedef unsigned short int word;    //16 бит
typedef word Adress;                //16 бит
typedef struct
{
    word adr;
    word val;
}Arg;                               //Тип данных для dd, ss, ...
typedef struct
{
    Arg dd;
    Arg ss;
}Param;                             //Аргументы для функций в одной структуре
typedef struct
{
    word mask;
    word opcode;
    char * name;
    char params;                    //000(XX)(R)(N)(SS)(DD) - 8 бит
    void (* do_func)(Param p);
}Command;                           //Описание для команд PDP-11
//====================

//Global variables
extern byte mem[MEMSIZE];           //Память
extern int current_log_lvl;         //Уровень логирования
extern word reg[8];                 //Регистры R0, ..., R8
//====================

//PDP main-functions
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void mem_dump(Adress start, word n);
void load_file();
void console_arg(int argc, char * argv[]);
Arg get_modereg(word w);
Param get_params(word w, char params);
void run();
//====================

//Modes
void mode0(Arg * res, int r);
void mode1(Arg * res, int r);
void mode2(Arg * res, int r);
void mode3(Arg * res, int r);
void mode4(Arg * res, int r);
void mode5(Arg * res, int r);
void mode6(Arg * res, int r);
void mode7(Arg * res, int r);
//====================

//PDP do-functions
void do_halt(Param p);
void do_mov(Param p);
void do_add(Param p);
void do_SOB(Param p);
void do_nothing(Param p);
void do_unknown(Param p);
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
