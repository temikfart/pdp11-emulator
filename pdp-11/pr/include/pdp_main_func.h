#pragma once

// Функции работы с памятью
void b_write(adress adr, byte b);
byte b_read(adress adr);
void w_write(adress adr, word w);
word w_read(adress adr);

void load_file();                           // Загрузка программы в эмулятор
void console_arg(int argc, char * argv[]);  // Разбор аргументов с консоли