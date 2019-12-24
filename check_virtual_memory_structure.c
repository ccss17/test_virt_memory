#include <stdio.h>
#include <stdlib.h>
#include "libkdump.h"

#define R "\033[31m"
#define G "\033[32m"
#define B "\033[34;1m"
#define E "\033[0m"

int data = 5555;
int bss = 0;
int bss2;

void text(){ 1+1 == 2; }

int main(int argc, char * argv[]){
    if (argc != 3) {
        fputs(R "Please pass TWO arguments...\n" E , stderr);
        return 1;
    }
    static char * data2 = "twice";
    int stack = 78;
    int stack2 = 23;
    int * heap = (int *)malloc(sizeof(int));
    int * heap2 = (int *)malloc(sizeof(int));
    char * environment_variable = getenv("PATH");

    printf("Let's check addresses of each memory section of virtual memory system.\n");
    printf(G"Text  section " E " : " B "%p\n", text);
    printf(G"Data  section " E " : " B "%p\n", &data2);
    printf(G"              " E " : " B "%p\n", &data);
    printf(G"BSS   section " E " : " B "%p\n", &bss);
    printf(G"              " E " : " B "%p\n", &bss2);
    printf(G"Heap  section " E " : " B "%p\n", heap);
    printf(G"              " E " : " B "%p\n", heap2);
    printf(G"Main arg-argc " E " : " B "%p\n", &argc);
    printf(G"Stack section " E " : " B "%p\n", &stack);
    printf(G"              " E " : " B "%p\n", &stack2);
    printf(G"Main arg-argv " E " : " B "%p\n", argv);
    printf(G"     argv[1]  " E " : " B "%p\n", argv[1]);
    printf(G"     argv[2]  " E " : " B "%p\n", argv[2]);
    printf(G"Env variable  " E " : " B "%p\n", environment_variable);
    printf(R "These are Virtual Address\n\n"E);

    printf("Let's check physical addresses(Real Address)!\n");
    void * physical_text = libkdump_virt_to_phys((size_t)text);
    if (physical_text == NULL) {
        puts(R "If you want to see physical memory address, reexecute with root privileges!"E);
        return 1;
    }
    printf(G"Text  section " E " : " B "%p\n", physical_text);
    printf(G"Data  section " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&data2));
    printf(G"              " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&data));
    printf(G"BSS   section " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&bss));
    printf(G"              " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&bss2));
    printf(G"Heap  section " E " : " B "%p\n", libkdump_virt_to_phys((size_t)heap));
    printf(G"              " E " : " B "%p\n", libkdump_virt_to_phys((size_t)heap2));
    printf(G"Main arg-argc " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&argc));
    printf(G"Stack section " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&stack));
    printf(G"              " E " : " B "%p\n", libkdump_virt_to_phys((size_t)&stack2));
    printf(G"Main argument " E " : " B "%p\n", libkdump_virt_to_phys((size_t)argv));
    printf(G"     arg-argv " E " : " B "%p\n", libkdump_virt_to_phys((size_t)argv));
    printf(G"     argv[1]  " E " : " B "%p\n", libkdump_virt_to_phys((size_t)argv[1]));
    printf(G"     argv[2]  " E " : " B "%p\n", libkdump_virt_to_phys((size_t)argv[2]));
    printf(G"Env variable  " E " : " B "%p\n", libkdump_virt_to_phys((size_t)environment_variable));
    printf(R "These are real Physical Address\n"E);
    return 0;
}

