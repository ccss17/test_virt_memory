override CFLAGS += -O3 -pthread -Wno-attributes -m64 -Wall -Wextra -pedantic 
CC=gcc

SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)

all: $(BINARIES)

meltdown/libkdump/libkdump.a:  libkdump/libkdump.c
	if [[ ! -d meltdown ]]; then
		git clone https://github.com/IAIK/meltdown
		make -C meltdown
	fi
	make -C libkdump

%: %.c libkdump/libkdump.a
	$(CC) $< -o $@ -m64 -Llibkdump -Ilibkdump -lkdump -static $(CFLAGS)
	
clean:
	rm -f *.o $(BINARIES)
	make clean -C meltdown
