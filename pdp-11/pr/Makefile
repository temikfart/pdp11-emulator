IDIR=include
CC=gcc
CFLAGS=-I$(IDIR) -g
BIN=pdp11.exe


SDIR=src
ODIR=obj


_DEPS = pdp.h pdp_add-func.h pdp_do-func.h pdp_main-func.h pdp_run.h pdp_tests.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = pdp_main.o pdp_main-func.o pdp_add-func.o pdp_tests.o pdp_run.o pdp_do-func.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: $(BIN)


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean


clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(INCDIR)/*~