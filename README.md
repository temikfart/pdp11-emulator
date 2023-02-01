# PDP-11 Emulator
-----------------

The PDP-11 is a series of 16-bit minicomputers sold by DEC from 1970 into the 1990s.

Our project is a PDP-11 emulator.
Due to the limited time for development, we have implemented only a part of the functions.


## What can the emulator do? What features are implemented?
-------------------------------------------------

At the moment, our emulator has a program loading function,
which may include the following commands:
```
add      Addition
mov      Assignment
movb     Bitwise assignment
cmp      Comparing two words without changes
cmpb     Compare two bytes without changes
sob      Summation of an array of integers

clr      Clear register
tst      Test command to set flags N and Z, and V, C to 0
tstb     Test command to set flags N and Z, and V, C to 0

ccc      Set all flags to 0
cln      Set flag N to 0
clz      Set the Z flag to 0
clv      Set flag V to 0
clc      Set flag C to 0

scc      Set all flags to 1
sen      Set flag N to 1
sez      Set the Z flag to 1
sev      Set V flag to 1
sec      Set flag C to 1

br       Br (Branching)
bcc      Br if C = 0
bcs      Br if C = 1
beq      Br if Z = 0
bge      Br if N and V = 0
bgt      Br if Z or (N and V) = 0
bhi      Br if C or Z = 0
ble      Br if Z or (N and V) = 1
blt      Br if N and V = 1
blo      Br if C = 1
bmi      Br if N = 1
bne      Br if Z = 1
bpl      Br if N = 0
bvc      Br if V = 0
bvs      Br if V = 1

halt     Stop the program
nop      No operation
```


## How to run our emulator?
------------------------------

Once you have downloaded all the source code for the emulator, you will need to run it.
To do this, you can use the Ubuntu command line:

1. Launch the Ubuntu command line;
2. Go to the directory with the `pdp11.exe` file;
3. Run `Makefile` with the `make` command;
4. After compilation, run the emulator with the command `./pdp11.exe`;
5. You will see **USAGE**:

```
USAGE: pdp11.exe [options] [file]

Options:
  -d  set debug print-lvl
  -t  set trace print-lvl

File:
  filepath  path to your programm     Example: ../programs/my_pr.o
```
6. Have fun.


## How to test the PDP-11 emulator?
--------------------------------------

>Perhaps our [tests](https://github.com/tatyderb/pdp11_tests) will be useful to you.

In order to test your program on the PDP-11 emulator, you will need:
1. The `as11` translator, which can be downloaded here:

    [Linux](http://acm.mipt.ru/twiki/pub/Cintro/PDPIntro/pdp11em-linux.zip)
    
    [Windows](http://acm.mipt.ru/twiki/pub/Cintro/PDPIntro/pdp11em-win32.rar)
    
    [Mac OS](http://acm.mipt.ru/twiki/pub/Cintro/PDPIntro/mac_exe.zip)
    
3. Command line.

To write a program that will be accepted by the emulator you will need:
1. Write your assembler code as a text file;
2. Run the translator `as11.exe` from the command line.
   To create a file that will contain machine code for the PDP-11 emulator,
   you need to enter the following command:
```
>./as11.exe -l [listing] -o [object] [your program]

[listing]         Path for listing file         *.l   Example: /tests/sum/mytest_sum.l
[object]          Path for object file          *.o   Example: /tests/sum/mytest_sum.o
[your program]    Your assembly lang programm         Example: /tests/sum/mytest_sum

Example:

>./as11.exe -l /tests/sum/mytest_sum.l -o /tests/sum/mytest_sum.o /tests/sum/mytest_sum

...   //We are here
|__Folder1
|__Folder2
|__tests
.  |__sum
.  .  |__mytest_sum
.  .  |__mytest_sum.l
.  .  |__mytest_sum.o
.  |__subtr
.  |__div
|__Folder3
```


## Developers
---------------

#### Artyom Fartygin ([temikfart](https://github.com/temikfart))


#### Roman Gankov ([hankou](https://github.com/hankou-code))


## Mentors
-------------

#### Georgiy Vinogradov ([gvino](https://github.com/gvino))

#### Tatyana Derbysheva ([tatyderb](https://github.com/tatyderb))
