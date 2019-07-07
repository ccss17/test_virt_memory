#include <stdio.h>
#include <stdlib.h>
#include "libkdump.h"

int data = 5555;
int bss = 0;
int bss2;

void text(){ 1+1 == 2; }

int main(int argc, char * argv[]){
    static char * data2 = "twice";
    int stack = 78;
    int stack2 = 23;
    int * heap = (int *)malloc(sizeof(int));
    int * heap2 = (int *)malloc(sizeof(int));
    char * environment_variable = getenv("PATH");

    printf("Let's check address of each memory section from BOTTOM to TOP.\n");
    printf("Text  section : %p\n", text);
    printf("Data  section : %p\n", &data);
    printf("              : %p\n", &data2);
    printf("BSS   section : %p\n", &bss);
    printf("              : %p\n", &bss2);
    printf("Heap  section : %p\n", heap);
    printf("              : %p\n", heap2);
    printf("Stack section : %p\n", &stack);
    printf("              : %p\n", &stack2);
    printf("Main argument : %p\n", argv);
    printf("Environment   : %p\n", environment_variable);
    printf("All of these are Virtual Address\n\n");

    printf("Let's check physical address(Real Address)!\n");
    void * physical_text = libkdump_virt_to_phys((size_t)text);
    if (physical_text == NULL) {
        puts("\x1b[31mIf you want to see physical memory address, reexecute with root privileges!");
        return 1;
    }
    printf("Text  section : %p\n", physical_text);
    printf("Data  section : %p\n", libkdump_virt_to_phys((size_t)&data));
    printf("              : %p\n", libkdump_virt_to_phys((size_t)&data2));
    printf("BSS   section : %p\n", libkdump_virt_to_phys((size_t)&bss));
    printf("              : %p\n", libkdump_virt_to_phys((size_t)&bss2));
    printf("Heap  section : %p\n", libkdump_virt_to_phys((size_t)heap));
    printf("              : %p\n", libkdump_virt_to_phys((size_t)heap2));
    printf("Stack section : %p\n", libkdump_virt_to_phys((size_t)&stack));
    printf("              : %p\n", libkdump_virt_to_phys((size_t)&stack2));
    printf("Main argument : %p\n", libkdump_virt_to_phys((size_t)argv));
    printf("Environment   : %p\n", libkdump_virt_to_phys((size_t)environment_variable));
    return 0;
}
