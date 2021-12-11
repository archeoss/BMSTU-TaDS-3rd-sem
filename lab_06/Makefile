CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99  -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
CONST_HEAD := $(INCDIR)/errors.h $(INCDIR)/structures.h $(INCDIR)/colors.h
OBJS := $(ODIR)/io.o $(ODIR)/operations.o $(ODIR)/graphvis.o $(ODIR)/hash.o $(ODIR)/timer.o 
LIBS := -Iinc 

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@

$(ODIR)/io.o : $(SRCDIR)/io.c $(INCDIR)/io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/io.c -o $@ $(LIBS)

$(ODIR)/hash.o : $(SRCDIR)/hash.c $(INCDIR)/hash.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/hash.c -o $@ $(LIBS)

$(ODIR)/timer.o : $(SRCDIR)/timer.c $(INCDIR)/timer.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/timer.c -o $@ $(LIBS)

$(ODIR)/graphvis.o : $(SRCDIR)/graphvis.c $(INCDIR)/graphvis.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/graphvis.c -o $@ $(LIBS)

$(ODIR)/operations.o : $(SRCDIR)/operations.c $(INCDIR)/operations.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/operations.c -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f $(ODIR)/*.o *.exe vgcore.*
