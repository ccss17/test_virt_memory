# Some experiments on virtual memory system 

## Get source and compile

```shell
git clone https://github.com/ccss17/test_virt_memory
cd test_virt_memory
make
```

## Test 1

Checking the memory structure of the virtual memory system and checking each physical memory address by using [meltdown's POC library](https://github.com/IAIK/meltdown) `libkdump` 

```shell
sudo ./check_virtual_memory_structure HELLO WOLRD
```

![check_virtual_memory_structure](https://user-images.githubusercontent.com/16812446/73173290-623f7c80-4148-11ea-8b84-1caac1f4a712.png)


## Test 2

Accessing virtual memory space of other process and modify it. (source from https://github.com/holbertonschool/Hack-The-Virtual-Memory ([hack_virt_test.c](https://github.com/holbertonschool/Hack-The-Virtual-Memory/blob/master/00.%20C%20strings%20%26%20the%20proc%20filesystem/loop.c), [hack_virt.py](https://github.com/holbertonschool/Hack-The-Virtual-Memory/blob/master/01.%20Python%20bytes/read_write_heap.py)))

```shell
./hack_virt_test             # load program and load string "Holberton" to heap
ps -ef | grep hack_virt_test # check PID of "hack_virt_test"
sudo ./hack_virt_test.py 11127 Holberton TEST
```

![hack_virt_test](https://user-images.githubusercontent.com/16812446/72776210-b03e1700-3c54-11ea-9e2d-24629826cbe7.gif)
