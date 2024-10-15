CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
DEBUG = -g
OBJ = main.o linkedList.o terminal.o
EXEC = myProgram

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c main.h linkedList.h terminal.h
	$(CC) $(CFLAGS) main.c -c

linkedList.o : linkedList.c linkedList.h
	$(CC) $(CFLAGS) linkedList.c -c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c
