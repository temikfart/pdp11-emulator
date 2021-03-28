#include <stdio.h>
#include <stdarg.h>
#include "pdp.h"

byte mem[MEMSIZE];

int main(int argc, char * argv[])
{
    //Тест на нечетный адрес
    //test_odd_adr();
    
    //Тесты на чтение и запись слов
    test_mem();
    
    if(argc == 2)
    {
        load_file(argv[1]);
    }
    
    //Проверка logger'а
    test_logger();
    
    return 0;
}
