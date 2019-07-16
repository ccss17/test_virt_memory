#include <stdio.h>
#include <stdlib.h>
#include "libkdump.h"

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34;1m"
#define RESET   "\033[0m"

int data = 5555;
int bss = 0;
int bss2;

void text(){ 1+1 == 2; }

int main(int argc, char * argv[]){
    if (argc < 2) {
        fputs(RED "Please pass some arguments...\n" RESET , stderr);
        return 1;
    }
    static char * data2 = "twice";
    int stack = 78;
    int stack2 = 23;
    int * heap = (int *)malloc(sizeof(int));
    int * heap2 = (int *)malloc(sizeof(int));
    char * environment_variable = getenv("PATH");

    printf(YELLOW "Let's check address of each memory section from BOTTOM to TOP.\n" RESET);
    printf( GREEN "Text  section " RESET " : " BLUE "%p\n", text);
    printf( GREEN "Data  section " RESET " : " BLUE "%p\n", &data);
    printf( GREEN "              " RESET " : " BLUE "%p\n", &data2);
    printf( GREEN "BSS   section " RESET " : " BLUE "%p\n", &bss);
    printf( GREEN "              " RESET " : " BLUE "%p\n", &bss2);
    printf( GREEN "Heap  section " RESET " : " BLUE "%p\n", heap);
    printf( GREEN "              " RESET " : " BLUE "%p\n", heap2);
    printf( GREEN "Stack section " RESET " : " BLUE "%p\n", &stack);
    printf( GREEN "              " RESET " : " BLUE "%p\n", &stack2);
    printf( GREEN "Main arg-argc " RESET " : " BLUE "%p\n", &argc);
    printf( GREEN "     arg-argv " RESET " : " BLUE "%p\n", argv);
    printf( GREEN "     argv[1]  " RESET " : " BLUE "%p\n", argv[1]);
    printf( GREEN "Environment   " RESET " : " BLUE "%p\n", environment_variable);
    printf(RESET "All of these are Virtual Address\n\n");

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
