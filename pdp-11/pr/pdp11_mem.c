#include <stdio.h>
#include <assert.h>
#include "pdp11_mem.h"

byte mem[MEMSIZE];

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
    assert(adr % 2 == 0);
    
    word w = ((word)mem[adr+1]) << 8;
    w = w | (mem[adr] & 0xFF);
    
    return w;
}

//void test_mem();
//void test_odd_adr(Adress adr);

int main()
{
    //Тест на нечетный адрес
    //test_odd_adr();
    
    //Тесты на чтение и запись слов
    //test_mem();
    
    //load_file();
    Adress bl_adr;
    word bl_size;
    
    FILE *fout = fopen("out.txt", "w");
    
    while(2 == fscanf(stdin, "%04hx %04hx", &bl_adr, &bl_size))
    {
        fprintf(fout, "%04hx %04hx\n", bl_adr, bl_size);
        
        for(word i = 0x0000; i < bl_size; i++)
        {
            byte bl_byte;
            fscanf(stdin, "%02hhx", &bl_byte);
            
            fprintf(fout, "%02hhx\n", bl_byte);
        }
    }
    fclose(fout);
    
    
    return 0;
}
