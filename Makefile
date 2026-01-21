CC = gcc
CFLAGS = -Wall
DATA_FILE = test2.bin

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
	./projektpp $(DATA_FILE)

rundata: datagen
	./datagen $(DATA_FILE)

datagen: datagen.o
	$(CC) datagen.o -o datagen
	
datagen.o:
	$(CC) $(CFLAGS) -c datagen.c

clean:
	rm -f *.o projektpp datagen
