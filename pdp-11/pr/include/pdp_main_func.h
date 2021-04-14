#pragma once

// Save state 4 flags in the last 4 bits:
// process_state_word == 0000NZVC
// N -- negative (1 | 0)
// Z -- zero (1 | 0)
// V -- overflow (1 | 0)
// C -- carry (1 | 0)
// they are defined last completed command
extern byte psw;

// Функции работы с памятью
void b_write(adress adr, byte b);
byte b_read(adress adr);
void w_write(adress adr, word w);
word w_read(adress adr);

void load_file();                           // Загрузка программы в эмулятор
void console_arg(int argc, char * argv[]);  // Разбор аргументов с консоли
