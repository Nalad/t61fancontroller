CC = gcc
CFLAGS = -std=c99

main: main.o
	$(CC) -o main main.o

main.o: main.c
	$(CC) -c -o main.o main.c
