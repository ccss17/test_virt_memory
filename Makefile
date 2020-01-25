override CFLAGS += -O3 -pthread -Wno-attributes -m64 -Wall -Wextra -pedantic 
CC=gcc

SOURCES := $(wildcard *.c)
BINARIES := $(SOURCES:%.c=%)
LIBKDUMP := libkdump

all: $(BINARIES)

libkdump/libkdump.a: libkdump libkdump/libkdump.c
	make -C libkdump

libkdump:
	mkdir $(LIBKDUMP)
	curl -so $(LIBKDUMP)/Makefile https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/Makefile
	curl -so $(LIBKDUMP)/libkdump.c https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/libkdump.c
	curl -so $(LIBKDUMP)/libkdump.h https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/libkdump.h

%: %.c libkdump/libkdump.a
	$(CC) $< -o $@ -m64 -Llibkdump -Ilibkdump -lkdump -static $(CFLAGS)
	
clean:
	rm -f *.o $(BINARIES)
	make clean -C libkdump
