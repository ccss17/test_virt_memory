override CFLAGS += -O3 -pthread -Wno-attributes -m64 -Wall -Wextra -pedantic 
CC=gcc

SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: $(BINARIES)

libkdump/libkdump.a:  libkdump/libkdump.c
	make -C libkdump

%: %.c libkdump/libkdump.a
	$(CC) $< -o $@ -m64 -Llibkdump -Ilibkdump -lkdump -static $(CFLAGS)
	
clean:
	rm -f *.o $(BINARIES)
	make clean -C libkdump
