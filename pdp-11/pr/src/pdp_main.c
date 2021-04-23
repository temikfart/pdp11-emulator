#include <stdio.h>
#include <stdarg.h>
#include "pdp.h"
#include "pdp_main_func.h"
#include "pdp_tests.h"

int current_log_lvl = INFO;

word reg[8];

PSW psw = {0, 0, 0, 0};

int main(int argc, char *argv[]) {
  // Разбор аргументов (флаги, файлы)
  console_arg(argc, argv);
  
  // Запуск программы
  run();
  
  // Тест с различными аргументами
  //test_console_arg();
  
  // Тест на нечетный адрес
  //test_odd_adr();
  
  // Тесты на чтение и запись слов
  //test_mem();
  
  // Тест: Проверка logger'а
  //test_logger();
  
  return 0;
}
