#include <stdio.h>
#include <assert.h>
#include "pdp11_mem.h"

void b_write(Adress adr, byte b)
{
    mem[adr] = b;
}
byte b_read(Adress adr)
{
    return mem[adr] & 0xFF;
}
void w_write(Adress adr, word w)
{
    assert(adr % 2 == 0);
    
    mem[adr] = (byte)w & 0xFF;
    mem[adr+1] = (byte)(w >> 8) & 0xFF;
}
word w_read(Adress adr)
{
    word w = ((word)mem[adr+1]) << 8;
    //printf("w = %x\n", w);
    w = w | (mem[adr] & 0xFF);
    
    return w;
}

//void test_mem();
//void test_odd_adr(Adress adr);

int main()
{
    //Тест на нечетный адрес
    //Adress adr_odd = 3;
    //test_odd_adr(adr_odd);
    
    //Тесты на чтение и запись слов
    test_mem();
    
    return 0;
}

