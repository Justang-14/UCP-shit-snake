CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
DEBUG = -g
OBJ = main.o linkedList.o
EXEC = myProgram

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c main.h
	$(CC) $(CFLAGS) main.c -c

linkedList.o : linkedList.c linkedList.h
	$(CC) $(CFLAGS) linkedList.c -c

#bounds.o : bounds.o bounds.h
#	$(CC) $(CFLAGS) bounds.c -c