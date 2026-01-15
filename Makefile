CC = gcc
CFLAGS = -Wall

all: projektpp

projektpp: main.o menu.o data.o file.o
	$(CC) main.o menu.o data.o file.o -o projektpp

main.o: main.c menu.h
	$(CC) $(CFLAGS) -c main.c

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c 

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c

run: all
	./projektpp test.txt

clean:
	rm -f *.o projektpp
