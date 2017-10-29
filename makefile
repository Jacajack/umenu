CC = gcc
CFLAGS = -Wall -I./include
LD = ld
AR = ar

all: clean force lib/libumenu.a

lib/libumenu.a: obj/core.o obj/umenu.o obj/umenuprint.o
	$(AR) -cvq $@ $^
	$(AR) -t $@

obj/core.o: src/core.c
	$(CC) $(CFLAGS) -c $^ -o $@

obj/umenu.o: src/umenu.c
	$(CC) $(CFLAGS) -c $^ -o $@

obj/umenuprint.o: src/umenuprint.c
	$(CC) $(CFLAGS) -c $^ -o $@

examples: all
	-mkdir bin
	gcc -o bin/demo examples/demo.c -lncurses -Llib -lumenu -Iinclude -Wall

force:
	-mkdir obj
	-mkdir lib

clean:
	-rm -rf obj
	-rm -rf lib
	-rm -rf bin
