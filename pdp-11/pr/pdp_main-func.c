#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "pdp.h"

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
    for(word j = 0; j < n; j++, start++)
    {
        fprintf(stdout, "%04hx : %02hhx\n", start, b_read(start));
    }
    printf("\n");
}
void load_file(const char *filename)
{
    Adress bl_adr;
    word bl_size;
    
    FILE *fin = fopen(filename, "r");
    if(errno)
    {
        char *ans = malloc((strlen(filename) + 50) * sizeof(char));
        sprintf(ans, "Can't open file: %s\n", filename);
        perror(ans);
        free(ans);
        exit(1);
    }
    
    while(2 == fscanf(fin, "%hx%hx", &bl_adr, &bl_size))
    {
        for(word i = 0; i < bl_size; i++, bl_adr++)
        {
            byte bl_byte;
            fscanf(fin, "%hhx", &bl_byte);
            
            b_write(bl_adr, bl_byte);
        }
        //Печать из памяти mem
        mem_dump(bl_adr - (Adress)bl_size, bl_size);
    }
    fclose(fin);
}