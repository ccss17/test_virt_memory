override CFLAGS += -O3 -pthread -Wno-attributes
CC=gcc

all: libkdump.a 

libkdump.o: libkdump.c
	$(CC) -c -m64 -fPIC libkdump.c -o libkdump.o $(CFLAGS)
	
libkdump.a: libkdump.o
	ar rcs libkdump.a libkdump.o 

clean:
	rm -f *.o *.so *.a
