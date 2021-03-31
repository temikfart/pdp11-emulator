#pragma once

//Constants

//Наличие аргументов в функции
#define NO_PARAM 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8
#define HAS_XX 16
//====================

//Структуры
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

//Моды
void mode0(Arg * res, int r);
void mode1(Arg * res, int r);
void mode2(Arg * res, int r);
void mode3(Arg * res, int r);
void mode4(Arg * res, int r);
void mode5(Arg * res, int r);
void mode6(Arg * res, int r);
void mode7(Arg * res, int r);
//====================

//Функции
Arg get_modereg(word w);
Param get_params(word w, char params);
//====================

//do-функции
void do_halt(Param p);
void do_mov(Param p);
void do_add(Param p);
void do_SOB(Param p);
void do_nothing(Param p);
void do_unknown(Param p);
//====================
