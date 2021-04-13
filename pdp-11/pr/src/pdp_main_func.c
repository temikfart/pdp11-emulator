#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pdp.h"
#include "pdp_add_func.h"

#define MEMSIZE (64*1024)   // Размер памяти PDP-11

byte mem[MEMSIZE];
byte process_state_word;

void b_write(adress adr, byte b) {
  if (adr < 8) {
    if ((b >> 7) == 0) {
      reg[adr] = (word)b;
    } else {
      reg[adr] = (word)b | 0xFF00;
    return;
    }
  }
  
  mem[adr] = b;
}
byte b_read(adress adr) {
  return mem[adr] & 0xFF;
}
void w_write(adress adr, word w) {
  if (adr < 8) {
    reg[adr] = w;
    return;
  }
  
  assert(adr % 2 == 0);
  
  mem[adr] = (byte)w & 0xFF;
  mem[adr+1] = (byte)(w >> 8) & 0xFF;
  
  return;
}
word w_read(adress adr) {
  if (adr < 8) {
    return reg[adr];
  }
  
  assert(adr % 2 == 0);
  
  word w = ((word)mem[adr+1]) << 8;
  w = w | (mem[adr] & 0xFF);
  
  return w;
}
void mem_dump(adress start, word n) {
  for (word j = 0; j < n; j++) {
    fprintf(stdout, "%04hx : %02hhx\n", start, b_read(start+j));
  }
  printf("\n");
}
void load_file(const char *filename) {
  adress bl_adr;
  word bl_size;
  
  FILE *fin = fopen(filename, "r");
  if (errno) {
    char *ans = malloc((strlen(filename) + 50) * sizeof(char));
    sprintf(ans, "Can't open file: %s", filename);
    perror(ans);
    free(ans);
    exit(1);
  }
  
  while (2 == fscanf(fin, "%hx%hx", &bl_adr, &bl_size)) {
    for (word i = 0; i < bl_size; i++) {
      byte bl_byte;
      fscanf(fin, "%hhx", &bl_byte);
      
      b_write(bl_adr + i, bl_byte);
    }
    // Печать из памяти mem
    if (current_log_lvl > TRACE) {
      mem_dump(bl_adr - (adress)bl_size, bl_size);
    }
  }
  fclose(fin);
}
void print_instruction(char *str) {
  // Usage
  printf("Usage: pdp11 [options] [file]\n\n");
  
  // Options
  printf("Options:\n");
  printf("\t-d \t set debug print-lvl\n");
  printf("\t-t \t set trace print-lvl\n");
}
void console_arg(int argc, char *argv[]) {
  //current_log_lvl = SILENT;  
  int flag = 0;
  opterr = 0;

  if (argc == 1) {  // program started with no arguments
    print_instruction(argv[0]);  // file name
    exit(0);
  }

  while ((flag = getopt(argc, argv, "dt")) != -1) {
    switch (flag) {
      case 'd':
        current_log_lvl = (DEBUG > current_log_lvl) ? DEBUG : current_log_lvl;
        logger(DEBUG, "flag -d: debug.\n");
        break;
      case 't':
        current_log_lvl = (TRACE > current_log_lvl) ? TRACE : current_log_lvl;
        logger(DEBUG, "flag -t: trace.\n");
        break;
      case '?':
        logger(ERROR, "Unknown flag: -%c\n", optopt);
        break;
      default:
        logger(ERROR,
               "In console_arg function: default condition was activated.\n");
        exit(1);
    }
  }

  for (int i = optind; i < argc; i++) {
    load_file(argv[i]);
  }
}
