#define MEMSIZE (64*1024)

typedef unsigned char byte;         //8 bit
typedef unsigned short int word;    //16 bit
typedef word Adress;                //16 bit

byte mem[MEMSIZE]; //Глобальная переменная

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem();
void test_odd_adr(Adress adr);