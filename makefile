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

force:
	-mkdir obj
	-mkdir lib

clean:
	-rm -rf obj
	-rm -rf lib
