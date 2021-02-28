#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBit(unsigned char a)
{
// значения битов записываются в строку
        char * tmp = calloc(10, sizeof(char));
// 8 знаков в строке устанавливаются равными символу '0'
        memset(tmp, '0', sizeof(char) * 8);
// Заполняем со старших адресов
        for (int i = 7 ; i > -1; i--)
        {
                tmp[i] = a % 2 + '0'; 
                a /= 2;
        }

    printf("%s\n", tmp);
    free(tmp);
}

int main()
{
    unsigned char x, y, res;
    //scanf("%hhu %hhu", x, y);
    
    //printf("%ld\n", sizeof(unsigned char));
    // XOR = (x | ~y) & (~x | y)
    
    x = 13; //0000 1101
    printf("~x: ");
    printBit(~x); //1111 0010
    
    y = 19; //0001 0011
    printf("-y: ");
    printBit(-y); //1110 1101
    
    printf("AND: ");
    printBit(x & y); //0000 0001 AND
    
    printf("OR: ");
    printBit(x | y); //0001 1111 OR
    
    printf("XOR: ");
    printBit(((~x) | y) &(x | (~y))); //1110 0001 XOR
    
    
    return 0;
}