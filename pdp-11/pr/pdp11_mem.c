#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;         //8 bit
typedef unsigned short int word;    //16 bit
typedef word Adress;                //16 bit

#define MEMSIZE (64*1024)

byte mem[MEMSIZE]; //Глобальная переменная

//Прототипы функций
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem()
{
    //Пишем байт, читаем байт
    Adress adr = 0;
    byte b0 = 0x0a;
    b_write(adr, b0);
    byte bres1 = b_read(adr);
    printf("b-w/b-r \t %02hhx = %02hhx\n", b0, bres1);
    assert(b0 == bres1);
    
    //Пишем 2 байта, читаем слово
    adr += 2;   //=2
    b0 = 0x0a;
    byte b1 = 0xcb;
    word w = 0xcb0a;
    b_write(adr, b0);
    b_write(adr + 1, b1);
    word wres = w_read(adr);
    printf("2b-w/w-r \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
    assert(w == wres);
    
    //Пишем слово, читаем слово
    adr += 2;   //=4
    w = 0xfd0e;
    w_write(adr, w);
    wres = w_read(adr);
    printf("w-w/w-r \t %04hx = %04hx\n", wres, w);
    assert(w == wres);
    
    //Пишем слово, читаем 2 байта
    adr += 2;   //=6
    w = 0xabcd;
    w_write(adr, w);
    bres1 = b_read(adr + 1);
    byte bres2 = b_read(adr);
    printf("w-w/2b-r \t %02hhx%02hhx = %04hx\n", bres1, bres2, w);
    assert(bres2 == 0xcd);
    assert(bres1 == 0xab);
}
void test_odd_adr(Adress adr)
{
    //Проверка на нечетный адрес
    assert((adr % 2) == 0);
}

int main()
{
    //Тест на нечетный адрес
    //Adress adr_odd = 3;
    //test_odd_adr(adr_odd);
    
    //Тесты на чтение и запись слов
    test_mem();
    
    return 0;
}

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
