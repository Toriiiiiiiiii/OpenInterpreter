CC = g++
LD = ar

CFLAGS = -g -c -Wall -Wpedantic -Werror
LDFLAGS = rcs

SRC = $(wildcard *.cc)
HDR = $(wildcard *.h)
OBJ = $(SRC:%.cc=../bin/obj/%.o)
BIN = ../bin/lib/libopeninterpreter.a

all: $(BIN)

$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) $(BIN) $(OBJ)

../bin/obj/%.o: %.cc $(HDR)
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -rf ../bin/lib/*
	mkdir ../bin/obj