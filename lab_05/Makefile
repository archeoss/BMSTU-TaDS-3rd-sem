CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99  -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
CONST_HEAD := $(INCDIR)/errors.h $(INCDIR)/structures.h $(INCDIR)/colors.h $(INCDIR)/arr_struct.h $(INCDIR)/list_struct.h 
OBJS := $(ODIR)/io.o $(ODIR)/arr_ao.o $(ODIR)/test_ao.o $(ODIR)/operations.o $(ODIR)/list_ao.o 
LIBS := -Iinc 

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@

$(ODIR)/io.o : $(SRCDIR)/io.c $(INCDIR)/io.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/io.c -o $@ $(LIBS)

$(ODIR)/operations.o : $(SRCDIR)/operations.c $(INCDIR)/operations.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/operations.c -o $@ $(LIBS)

$(ODIR)/arr_ao.o : $(SRCDIR)/arr_ao.c $(INCDIR)/arr_ao.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/arr_ao.c  -o $@ $(LIBS)

$(ODIR)/list_ao.o : $(SRCDIR)/list_ao.c $(INCDIR)/list_ao.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/list_ao.c  -o $@ $(LIBS)

$(ODIR)/test_ao.o : $(SRCDIR)/test_ao.c $(INCDIR)/test_ao.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/test_ao.c  -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f $(ODIR)/*.o *.exe vgcore.*
