# Эмулятор PDP-11
-----------------

PDP-11 — это серия 16-разрядных мини-ЭВМ компании DEC, серийно производившихся и продававшихся в 1970-80-х годах.

Наш проект — это эмулятор PDP-11.
В силу ограниченности нашего времени на разработку, мы реализовали лишь часть функций.


## Что эмулятор умеет? Какие функции реализованы?
-------------------------------------------------

На данный момент в нашем эмуляторе реализована функция загрузки программы, 
которая может включать в себя следующие команды:
```
add     Сложение
mov     Присваивание
movb    Побитовое присваивание
cmp     Сравнение двух слов без их изменения
cmpb    Сравнение двух байтов без их изменения
sob     Суммирование массива целых чисел

clr     Обнуление регистра
tst     Тестовая команда выставления флагов N и Z, а V, C на 0
tstb    Тестовая команда выставления флагов N и Z, а V, C на 0

ccc     Выставление всех флагов на 0
cln     Выставление флага N на 0
clz     Выставление флага Z на 0
clc     Выставление флага C на 0

scc     Выставление всех флагов на 1
sen     Выставление флага N на 0
sez     Выставление флага Z на 0
sec     Выставление флага C на 0

halt    Остановка программы
nop     Нет операций
```


## Как запустить наш эмулятор?
------------------------------

После того как вы скачали весь исходный код эмулятора вам нужно будет запустить его.
Для этого можно использовать командную строку Ubuntu:

1. Запустите командную строку Ubuntu;
2. Перейдите в директорию с файлом `pdp11.exe`;
3. Запустите `Makefile` с помощью команды `make`;
4. После компиляции, запустите эмулятор командой `./pdp11.exe`;
5. Вы увидите **USAGE**:
```
USAGE: pdp11.exe [options] [file]

Options:
  -d  set debug print-lvl
  -t  set trace print-lvl

File:
  /filepath/  путь до вашей программы, например, ../programs/my_pr.o
```
6. Приятного использования.


## Как протестировать эмулятор PDP-11?
--------------------------------------

Для того, чтобы протестировать на эмуляторе PDP-11 свою программу вам понадобится:
1. Переводчик `as11` (Находится в репозитории в папке *Папка с `as11.exe`*);
2. Командная строка.

Чтобы написать программу, которая будет принята эмулятором вам потребуется:
1. Напишите ваш ассемблер-код в виде текстового файла;
2. Запустите с помощью командной строки переводчик `as11.exe`.
Чтобы создать файл, который будет содержать машинный код для эмулятора PDP-11, 
вам нужно ввести следующую команду:
```
>./as11.exe -l [listing] -o [object] [your program]

[listing]         Путь для файла listing \*.l, например, ../tests/sum/mytest_sum.l
[object]          Путь для объектного файла \*.o, например, ../test/sum/mytest_sum.o
[your program]    Ваша программа на ассемблере, например, ../tests/sum/mytest_sum
```


## Разработчики
---------------

#### Артём Фартыгин ([temikfart](https://github.com/temikfart))


#### Роман Ганьков ([hankou](https://github.com/hankou-code))


## Наставники
-------------

#### Георгий Виноградов ([gvino](https://github.com/gvino))

#### Татьяна Дербышева ([tatyderb](https://github.com/tatyderb))
