IDIR =../include

CC=gcc
CFLAGS=-I$(IDIR) -Wall -Wpedantic -fopenmp

ODIR=../obj

_DEPS = escapeTimeAlg.h functions.h imUtil.h polynomial.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o escapeTimeAlg.o functions.o imUtil.o polynomial.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fractalC: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
