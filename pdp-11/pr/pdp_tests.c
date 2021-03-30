#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pdp.h"

void test_mem_1(word w, byte b1, byte b0)
{
    /*
    В тестах предполагается, что на вход идет слово w,
    которое состоит из байтов b0 и b1.
    */
    Adress adr = 0;
    
    logger(TRACE, "===Byte/Word Write/Read TESTs===\n\n");

    //Пишем байт, читаем байт
    b_write(adr, b0);
    byte bres = b_read(adr);
    logger(TRACE, "\n(w/r)Test 1: b-w/b-r \t\t %02hhx = %02hhx.\n", b0, bres);
    assert(b0 == bres);

    //Пишем 2 байта, читаем слово
    b_write(adr, b0);
    b_write(adr + 1, b1);
    word wres = w_read(adr);
    logger(TRACE, "(w/r)Test 2: 2b-w/w-r \t\t %04hx = %02hhx%02hhx.\n", wres, b1, b0);
    assert(w == wres);

    //Пишем слово, читаем слово
    adr += 2;           //Чтобы не перезаписывать данные предыдущих двух тестов
    w_write(adr, w);
    wres = w_read(adr);
    logger(TRACE, "(w/r)Test 3: w-w/w-r \t\t %04hx = %04hx.\n", wres, w);
    assert(w == wres);

    //Пишем слово, читаем 2 байта (адрес тот же)
    w_write(adr, w);
    byte bres2 = b_read(adr);
    byte bres1 = b_read(adr + 1);
    logger(TRACE, "(w/r)Test 4: w-w/2b-r \t\t %02hhx%02hhx = %04hx.\n", bres1, bres2, w);
    assert(bres2 == b0);
    assert(bres1 == b1);
    
    logger(TRACE, "\n");
}
void test_mem()
{
    test_mem_1(0xabcd, 0xab, 0xcd);
    test_mem_1(0x0a0b, 0x0a, 0x0b);
    test_mem_1(0x000f, 0x00, 0x0f);
}
void test_odd_adr()
{
    logger(TRACE, "===Odd Adress TEST===\n\n");
    
    //Проверка на нечетный адрес
    logger(TRACE, "\n\t(OddAdr) Test: Error\n");
    w_write(11, 0xabda);
}
void test_logger_prints()
{
    printf("Current log level: %d.\n", current_log_lvl);
    
    logger(FATAL, "Fatal: \t Program died\n");
    logger(INFO, "Info: \t Just information\n");
    logger(ERROR, "Error: \t I'd like to live\n");
    logger(TRACE, "Trace: \t RTX\n");
    logger(DEBUG, "Debug: \t Bug under the body\n");
}
void test_logger()
{
    printf("===Logger TESTs===\n\n");
    
    //Проверка на log_lvl
    printf("\n\t(Log) Test 1: log_lvl(2) + FATAL, INFO, ERROR.\n");
    current_log_lvl = INFO;
    test_logger_prints();
    
    //Проверка на mute logger
    printf("\n\t(Log) Test 2: log_lvl(-1).\n");
    current_log_lvl = SILENT;
    test_logger_prints();
    
    //Проверка на два одноуровневых вывода
    printf("\n\t(Log) Test 3: log_lvl(3) + FATAL, INFO, ERROR, TRACE*2.\n");
    current_log_lvl = TRACE;
    test_logger_prints();
    logger(TRACE, "Trace: \t RTX\n");
    
    //Проверка, что все уровни печатаются
    printf("\n\t(Log) Test 4: log_lvl(4) + 5 log prints.\n");
    current_log_lvl = DEBUG;
    test_logger_prints();
}
void test_console_arg_print(int test_argc, char * test_argv[])
{
    console_arg(test_argc, test_argv);
    test_logger_prints();
}
void test_console_arg()
{
    //Заводим переменные для аргументов
    int test_argc = 0;
    char * test_argv[5];
    
    printf("===Arguments From Console TESTs===\n\n");
    
    //Ничего (Ожидаем принт уровня логирования)
    printf("\t(Arg) Test 1: log_lvl(-1).\n");
    test_argc = 1;
    test_argv[0] = 0;
    test_console_arg_print(test_argc, test_argv);
    
    //Несколько флагов и файлов в различном порядке
    printf("\n\t(Arg) Test 2: flags, test data *2, log_lvl(4) and 5 log prints.\n");
    test_argc = 5;
    test_argv[1] = "-t";
    test_argv[2] = "test_arg.o";
    test_argv[3] = "-d";
    test_argv[4] = "test_arg.o";
    test_console_arg_print(test_argc, test_argv);
    
    //1 существующий, 1 несущ. флаг и 1 сущ., 1 несущ. файл
    printf("\n\t(Arg) Test 3: test data and error.\n");
    test_argc = 5;
    test_argv[2] = "-a";
    test_argv[3] = "test_arg.o";
    test_argv[4] = "abcd";
    test_console_arg_print(test_argc, test_argv);
}
