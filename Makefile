CC = g++

CFLAGS = -g -c -Wall -Wpedantic -Werror
LDFLAGS = -Lbin/lib -lopeninterpreter

SRC = $(wildcard src/*.cc)
HDR = $(wildcard src/*.h)
OBJ = $(SRC:src/%.cc=bin/obj/%.o)
BIN = bin/exec

LIB = bin/lib/libopeninterpreter.a

all: $(BIN)

$(BIN): $(OBJ) $(LIB)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(LIB): $(wildcard openinterpreter/*.cc) $(wildcard openinterpreter/*.h)
	$(MAKE) -C openinterpreter

bin/obj/%.o: src/%.cc $(HDR) $(LIB)
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -rf bin/*
	mkdir bin/obj