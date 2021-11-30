CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99 -Wfloat-conversion -Wfloat-equal -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
CONST_HEAD := $(INCDIR)/errors.h $(INCDIR)/list_oper.h $(INCDIR)/arr_io.h $(INCDIR)/list_io.h $(INCDIR)/structures.h $(INCDIR)/arr_oper.h $(INCDIR)/colors.h
OBJS := $(ODIR)/io.o $(ODIR)/arr_oper.o $(ODIR)/arr_io.o $(ODIR)/list_oper.o $(ODIR)/list_io.o 
LIBS := -Iinc 

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@

$(ODIR)/io.o : $(SRCDIR)/io.c $(INCDIR)/io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/io.c -o $@ $(LIBS)

$(ODIR)/arr_oper.o : $(SRCDIR)/arr_oper.c $(INCDIR)/arr_oper.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/arr_oper.c  -o $@ $(LIBS)

$(ODIR)/arr_io.o : $(SRCDIR)/arr_io.c $(INCDIR)/arr_io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/arr_io.c  -o $@ $(LIBS)

$(ODIR)/list_oper.o : $(SRCDIR)/list_oper.c $(INCDIR)/list_oper.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/list_oper.c  -o $@ $(LIBS)

$(ODIR)/list_io.o : $(SRCDIR)/list_io.c $(INCDIR)/list_io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/list_io.c  -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f $(ODIR)/*.o *.exe vgcore.*
