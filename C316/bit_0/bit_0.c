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
    scanf("%hhu %hhu", x, y);
    
    // XOR = (x | ~y) & (~x | y)
    
    return 0;
}