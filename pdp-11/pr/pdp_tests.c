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

    //Пишем байт, читаем байт
    b_write(adr, b0);
    byte bres = b_read(adr);
    printf("b-w/b-r \t %02hhx = %02hhx\n", b0, bres);
    assert(b0 == bres);

    //Пишем 2 байта, читаем слово
    b_write(adr, b0);
    b_write(adr + 1, b1);
    word wres = w_read(adr);
    printf("2b-w/w-r \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
    assert(w == wres);

    //Пишем слово, читаем слово
    adr += 2;           //Чтобы не перезаписывать данные предыдущих двух тестов
    w_write(adr, w);
    wres = w_read(adr);
    printf("w-w/w-r \t %04hx = %04hx\n", wres, w);
    assert(w == wres);

    //Пишем слово, читаем 2 байта (адрес тот же)
    w_write(adr, w);
    byte bres2 = b_read(adr);
    byte bres1 = b_read(adr + 1);
    printf("w-w/2b-r \t %02hhx%02hhx = %04hx\n", bres1, bres2, w);
    assert(bres2 == b0);
    assert(bres1 == b1);
}
void test_mem()
{
    test_mem_1(0xabcd, 0xab, 0xcd);
    test_mem_1(0x0a0b, 0x0a, 0x0b);
    test_mem_1(0x000f, 0x00, 0x0f);
}
void test_odd_adr()
{
    //Проверка на нечетный адрес
    w_write(1, 0xabda);
}
void test_logger_prints()
{
    printf("Current log level: %d\n", current_log_lvl);
    logger(INFO, "Info: \t Just information\n");
    logger(ERROR, "Error: \t I'd like to live\n");
    logger(TRACE, "Trace: \t RTX\n");
    logger(DEBUG, "Debug: \t Bug under the body\n");
}
void test_logger()
{
    //Проверка на log_lvl
    current_log_lvl = INFO;     //Ожидаем печать lvl + INFO & ERROR
    test_logger_prints();
    
    //Проверка на mute logger
    current_log_lvl = SILENT;     //Ожидаем печать lvl
    test_logger_prints();
    
    //Проверка на два одноуровневых вывода
    current_log_lvl = TRACE;     //Ожидаем печать lvl + INFO & ERROR & TRACE*2
    test_logger_prints();
    logger(TRACE, "Trace: \t RTX\n");
    
    //Проверка, что все уровни печатаются
    current_log_lvl = DEBUG;     //Ожидаем печать lvl + all prints
    test_logger_prints();
}
void test_console_arg_print(int test_argc, char * test_argv[])
{
    console_arg(test_argc, test_argv);
    //printf("Current log level: %d\n", current_log_lvl);
    test_logger_prints();
}
void test_console_arg()
{
    //Заводим переменные для аргументов
    int test_argc = 0;
    char * test_argv[5];
    //test_argv = (char *)malloc(sizeof(char) * 50);
    
    //Ничего (Ожидаем принт уровня логирования)
    printf("\tArg-Test 1\n");
    test_argc = 1;
    test_argv[0] = 0;
    test_console_arg_print(test_argc, test_argv);
    
    //Несколько флагов и файлов в различном порядке
    printf("\n\tArg-Test 2\n");
    test_argc = 5;
    test_argv[1] = "-t";
    test_argv[2] = "test_arg.o";
    test_argv[3] = "-d";
    test_argv[4] = "test_arg.o";
    test_console_arg_print(test_argc, test_argv);
    
    //1 существующий, 1 несущ. флаг и 1 сущ., 1 несущ. файл
    printf("\n\tArg-Test 3\n");
    test_argc = 5;
    test_argv[2] = "-a";
    test_argv[3] = "test_arg.o";
    test_argv[4] = "abcd";
    test_console_arg_print(test_argc, test_argv);
}
