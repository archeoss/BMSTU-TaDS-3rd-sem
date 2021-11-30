CC := gcc
KEYS := -g -Wall -Werror -Wredundant-decls -std=c99 -Wfloat-conversion -Wfloat-equal -Wpedantic -Wextra -Wvla
ODIR := ./out
SRCDIR := ./src
INCDIR := ./inc
OBJS := $(ODIR)/readme.o $(ODIR)/showme.o $(ODIR)/sort.o
LIBS := -Iinc

all : app.exe

app.exe : $(OBJS) $(ODIR)/main.o
	$(CC) $^ -o $@ $(LIBS)

$(ODIR)/readme.o : $(SRCDIR)/readme.c $(INCDIR)/readme.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/readme.c -o $@ $(LIBS)

$(ODIR)/showme.o : $(SRCDIR)/showme.c $(INCDIR)/showme.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/showme.c -o $@ $(LIBS)

$(ODIR)/sort.o : $(SRCDIR)/sort.c $(INCDIR)/sort.h $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/sort.c -o $@ $(LIBS)

$(ODIR)/main.o : $(SRCDIR)/main.c $(CONST_HEAD)
	$(CC) $(KEYS) -c $(SRCDIR)/main.c -o $@ $(LIBS)

clean :
	rm -f $(ODIR)/*.o *.exe
