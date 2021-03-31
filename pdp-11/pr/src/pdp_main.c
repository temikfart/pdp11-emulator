#include <stdio.h>
#include <stdarg.h>
#include "pdp.h"

byte mem[MEMSIZE];
int current_log_lvl = INFO;
word reg[8];

int main(int argc, char * argv[])
{
    //Разбор аргументов (флаги, файлы)
    console_arg(argc, argv);
    
    //Запуск программы
    run();
    
    //Тест с различными аргументами
    //test_console_arg();
    
    //Тест на нечетный адрес
    //test_odd_adr();
    
    //Тесты на чтение и запись слов
    //test_mem();
    
    //Тест: Проверка logger'а
    //test_logger();
    
    return 0;
}