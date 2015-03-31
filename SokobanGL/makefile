SRC=src/
BIN=bin/
INC=include/
OBJ=obj/

CC=g++
CFLAGS= -Iinclude -W -Wall -g -pedantic --std=c++11 -lm

all: SokobanGL
	echo "Compilation terminee !"

SokobanGL: SokobanGL.o Matrice.o
	$(CC) -o $(BIN)SokobanGL $(OBJ)SokobanGL.o $(OBJ)Matrice.o

Matrice.o: $(SRC)Matrice.cpp $(INC)Matrice.hpp
	$(CC) -o $(OBJ)Matrice.o -c $(SRC)Matrice.cpp $(CFLAGS)

SokobanGL.o: $(SRC)SokobanGL.cpp $(INC)Matrice.hpp
	$(CC) -o $(OBJ)SokobanGL.o -c $(SRC)SokobanGL.cpp $(CFLAGS)

clean:
	rm -rvf $(BIN)SokobanGL $(OBJ)*.o $(SRC)*~ $(INC)*~

exec:
	./$(BIN)SokobanGL

execfile:
	./$(BIN)SokobanGL README.txt