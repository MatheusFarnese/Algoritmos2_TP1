CC = gcc
LIBS = -lm -lstdc++
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/trie.o
HDRS = $(INC)/trie.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

all:  bin

bin: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/trie.o: $(HDRS) $(SRC)/trie.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/trie.o $(SRC)/trie.cpp

clean:
	rm -f $(EXE) $(OBJS)
