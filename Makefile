CC     = gcc
FLAGS  = -Wall -Wextra --pedantic
FLAGS += -g
FLAGS += -std=c11
BINDIR = bin
SRCDIR = src
INCDIR = inc
EXE    = $(shell basename $(CURDIR))

# add library folder and library below
LIBDIR = .
LIB    =

all: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE): $(SRCDIR)/*.c
	$(CC) $(FLAGS) -I./$(INCDIR) -L./$(LIBDIR) $^ -o $@ $(LIB)

clean:
	-rm $(BINDIR)/*
