CC = gcc
CFLAGS = -Wall

all: projektpp

projektpp: main.o menu.o
	$(CC) main.o menu.o -o projektpp

main.o: main.c menu.h
	$(CC) $(CFLAGS) -c main.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c 

run: all
	./projektpp

clean:
	rm -f *.o projektpp
