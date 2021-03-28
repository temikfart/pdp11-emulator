#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

byte mem[MEMSIZE];

int main(int argc, char * argv[])
{
    //Тест на нечетный адрес
    //test_odd_adr();
    
    //Тесты на чтение и запись слов
    //test_mem();
    
    if(argc == 2)
    {
        load_file(argv[1]);
    }
    
    
    return 0;
}
