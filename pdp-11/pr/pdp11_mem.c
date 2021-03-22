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
    byte b0 = 0x0a;
    //Пишем байт, читаем байт
    b_write(2, b0);
    byte bres = b_read(2);
    printf("b-w/b-r \t %02hhx = %02hhx\n", b0, bres);
    assert(b0 == bres);
    
    //Пишем 2 байта, читаем слово
    Adress a = 4;
    byte b1 = 0xcb;
    b0 = 0x0a;
    word w = 0xcb0a;
    b_write(a, b0);
    b_write(a + 1, b1);
    word wres = w_read(a);
    printf("2b-w/w-r \t %04hx = %02hhx%02hhx\n", wres, b1, b0);
    assert(w == wres);
    
    //Пишем слово, читаем слово
    Adress a2 = 6;
    word w2 = 0xfd0e;
    w_write(a2, w2);
    word wres2 = w_read(a2);
    printf("w-w/w-r \t %04hx = %04hx\n", wres2, w2);
    assert(w2 == wres2);
    
    //Пишем слово, читаем 2 байта
    Adress a3 = 8;
    word w3 = 0xabcd;
    w_write(a3, w3);
    byte b2 = b_read(a3);
    byte b3 = b_read(a3+1);
    word wres3 = ((word)b2) | (b3 << 8); 
    printf("w-w/2b-r \t %02hhx%02hhx = %04hx; wres3 = %04hx\n", b3, b2, w3, wres3);
    assert(w3 == wres3);
}

int main()
{
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
    byte b0, b1;
    
    //b0 = (byte)((w << 8) >> 8);
    b0 = (byte)w;
    mem[adr] = b0;
    b1 = (byte)(w >> 8);
    mem[adr+1] = b1;
}
word w_read(Adress adr)
{
    word w = ((word)mem[adr+1]) << 8;
    //printf("w = %x\n", w);
    w = w | (mem[adr] & 0xFF);
    return w;
}
