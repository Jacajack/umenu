CC = gcc
CFLAGS = -Wall -I./include
LD = ld
AR = ar

all: clean force obj/umenu.o lib/libumenu.a

lib/libumenu.a: obj/umenu.o
	$(AR) -cvq $@ $^
	$(AR) -t $@

obj/umenu.o: src/umenu.c
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
