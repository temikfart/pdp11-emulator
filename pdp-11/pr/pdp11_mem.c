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
void mem_dump(Adress start, word n)
{
    //fout = fopen("out.txt", "a");
    
    for(word j = 0x0000; j < n; j++, start++)
    {
        fprintf(stdout, "%04hx : %02hhx\n", start, b_read(start));
        //fprintf(fout, "%04hx : %02hhx\n", start, b_read(start));   //отладочная печать в файл
    }
    //fclose(fout);
}
void load_file()
{
    Adress bl_adr;
    word bl_size;
    
    //FILE *fout = fopen("out.txt", "w");
    
    while(2 == fscanf(stdin, "%04hx %04hx", &bl_adr, &bl_size))
    {
        //fprintf(fout, "%04hx %04hx\n", bl_adr, bl_size);    //отладка печать в файл
        
        for(word i = 0x0000; i < bl_size; i++, bl_adr++)
        {
            byte bl_byte;
            fscanf(stdin, "%02hhx", &bl_byte);
            
            b_write(bl_adr, bl_byte);
            
            //fprintf(fout, "%02hhx\n", b_read(bl_adr));             //отладочная печать в файл
        }
    }
    //fclose(fout);
}

int main()
{
    //Тест на нечетный адрес
    //test_odd_adr();
    
    //Тесты на чтение и запись слов
    //test_mem();
    
    load_file();
    
    
    Adress start = 0x0050;
    word n = 0x0004;
    mem_dump(start, n);
    
    start = 0x0070;
    n = 0x0003;
    mem_dump(start, n);
    
    
    return 0;
}
