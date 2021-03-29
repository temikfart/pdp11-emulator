CC=gcc
CFLAGS=-I -g.
DEPS = pdp.h
OBJ = pdp_main.o pdp_main-func.o pdp_add-func.o pdp_tests.o pdp_run.o pdp_do-func.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pdp11.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)