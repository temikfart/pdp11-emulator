#pragma once

#define pc reg[7]           // Program Counter

// Уровни логирования
#define FATAL 0
#define ERROR 1
#define INFO 2
#define TRACE 3
#define DEBUG 4
#define SILENT -1

typedef unsigned char byte;         //  8 бит
typedef unsigned short int word;    // 16 бит
typedef word adress;                // 16 бит

// Save state 4 flags
// N -- negative (1 | 0)
// Z -- zero (1 | 0)
// V -- overflow (1 | 0)
// C -- carry (1 | 0)
// they are defined last completed command
typedef struct {
  char N;
  char Z;
  char V;
  char C;
} PSW;

// Глобальные переменные
extern int current_log_lvl;         // Уровень логирования
extern word reg[8];                 // Регистры R0, ..., R7
extern PSW psw;

void run();
