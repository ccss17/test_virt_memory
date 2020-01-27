override CFLAGS += -O3 -pthread -Wno-attributes -m64 -Wall -Wextra -pedantic 
CC=gcc
LIBKDUMP := libkdump
TEST1 := check_virtual_memory_structure
TEST2 := hack_virt_test

all: $(TEST1) $(TEST2)

libkdump/libkdump.a: libkdump libkdump/libkdump.c
	make -C libkdump

libkdump:
	mkdir $(LIBKDUMP)
	curl -so $(LIBKDUMP)/Makefile https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/Makefile
	curl -so $(LIBKDUMP)/libkdump.c https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/libkdump.c
	curl -so $(LIBKDUMP)/libkdump.h https://raw.githubusercontent.com/IAIK/meltdown/master/libkdump/libkdump.h

$(TEST1): $(TEST1).c libkdump/libkdump.a
	$(CC) $< -o $@ -m64 -Llibkdump -Ilibkdump -lkdump -static $(CFLAGS)
	
$(TEST2): $(TEST2).c $(TEST2).py 
	$(CC) $< -o $@

$(TEST2).c: 
	curl -so $(TEST2).c https://raw.githubusercontent.com/holbertonschool/Hack-The-Virtual-Memory/master/00.%20C%20strings%20%26%20the%20proc%20filesystem/loop.c 

$(TEST2).py:
	curl -so $(TEST2).py https://raw.githubusercontent.com/holbertonschool/Hack-The-Virtual-Memory/master/01.%20Python%20bytes/read_write_heap.py

clean:
	rm -f *.o $(TEST1) $(TEST2)
	make clean -C libkdump

purge:
	rm -r libkdump
	rm hack_virt_test*

