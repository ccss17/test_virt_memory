#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libkdump.h"

#define R "\033[31;1m"
#define G "\033[32;1m"
#define B "\033[34;1m"
#define BB "\033[90;1m"
#define BC "\033[96;1m"
#define E "\033[0m"

extern int etext, edata, end;

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
    printf(G "Text  section " E BB "━┳━ " B "%p\n" E, text);
    printf(BB"   END of Text" E BB " ┗━ " B "%p\n" E, &etext);
    printf(G "Data  section " E BB "━┳━ " B "%p\n" E, &data2);
    printf(G "              " E BB " ┣━ " B "%p\n" E, &data);
    printf(BB"   END of Data" E BB " ┗━ " B "%p\n" E, &edata);
    printf(G "BSS   section " E BB "━┳━ " B "%p\n" E, &bss);
    printf(G "              " E BB " ┣━ " B "%p\n" E, &bss2);
    printf(BB"    END of BSS" E BB " ┗━ " B "%p\n" E, &end);
    printf(G "Heap  section " E BB "━┳━ " B "%p\n" E, heap);
    printf(G "              " E BB " ┗━ " B "%p\n" E, heap2);
    printf(BB"        ↕ empty space ↕\n"E);
    printf(G "main()   argc " E BB "━━━ " B "%p\n" E, &argc);
    printf(G "Stack section " E BB "━┳━ " B "%p\n" E, &stack);
    printf(G "              " E BB " ┗━ " B "%p\n" E, &stack2);
    printf(G "main()   argv " E BB "━┳━ " B "%p\n" E, argv);
    printf(BC" argv[1]%6s"    E BB " ┣━ " B "%p\n" E, argv[1], argv[1]);
    printf(BC" argv[2]%6s"    E BB " ┗━ " B "%p\n" E, argv[2], argv[2]);
    printf(G "Env variable  " E BB "━━━ " B "%p\n" E, environment_variable);
    printf(R "These are Virtual Address\n\n"E);

    printf("Let's check physical addresses(Real Address)!\n");
    void * physical_text = libkdump_virt_to_phys((size_t)text);
    if (physical_text == NULL) {
        puts(R "If you want to see physical memory address, reexecute with root privileges!"E);
        return 1;
    }
    printf(G "Text  section " E BB "━┳━ " B "%p\n" E, physical_text);
    printf(BB"   END of Text" E BB " ┗━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&etext));
    printf(G "Data  section " E BB "━┳━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&data2));
    printf(G "              " E BB " ┣━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&data));
    printf(BB"   END of Data" E BB " ┗━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&edata));
    printf(G "BSS   section " E BB "━┳━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&bss));
    printf(G "              " E BB " ┣━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&bss2));
    printf(BB"    END of BSS" E BB " ┗━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&end));
    printf(G "Heap  section " E BB "━┳━ " B "%p\n" E, libkdump_virt_to_phys((size_t)heap));
    printf(G "              " E BB " ┗━ " B "%p\n" E, libkdump_virt_to_phys((size_t)heap2));
    printf(G "main()   argc " E BB "━━━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&argc));
    printf(G "Stack section " E BB "━┳━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&stack));
    printf(G "              " E BB " ┗━ " B "%p\n" E, libkdump_virt_to_phys((size_t)&stack2));
    printf(G "main()   argv " E BB "━┳━ " B "%p\n" E, libkdump_virt_to_phys((size_t)argv));
    printf(BC" argv[1]%6s"    E BB " ┣━ " B "%p\n" E, argv[1], libkdump_virt_to_phys((size_t)argv[1]));
    printf(BC" argv[2]%6s"    E BB " ┗━ " B "%p\n" E, argv[2], libkdump_virt_to_phys((size_t)argv[2]));
    printf(G "Env variable  " E BB "━━━ " B "%p\n" E, libkdump_virt_to_phys((size_t)environment_variable));
    printf(R "These are Physical Address(real RAM address)\n"E);
    return 0;
}

