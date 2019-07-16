#include <stdio.h>
#include <stdlib.h>
#include "libkdump.h"

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34;1m"
#define RESET   "\033[0m"

int main(int argc, char * argv[]){
    if (argc < 2) {
        fputs(RED "Please pass some arguments...\n" RESET , stderr);
        return 1;
    }
    int stack = 78;
    int stack2 = 23;
    char * environment_variable = getenv("PATH");

    printf(YELLOW "Let's check address of each memory section from BOTTOM to TOP.\n" RESET);
    printf( GREEN "Stack section " RESET " : " BLUE "%p\n", &stack);
    printf( GREEN "              " RESET " : " BLUE "%p\n", &stack2);
    printf( GREEN "Main arg-argc " RESET " : " BLUE "%p\n", &argc);
    printf( GREEN "     arg-argv " RESET " : " BLUE "%p\n", argv);
    printf( GREEN "     argv[1]  " RESET " : " BLUE "%p\n", argv[1]);
    printf( GREEN "Environment   " RESET " : " BLUE "%p\n", environment_variable);
    printf(RESET "All of these are Virtual Address\n\n");
    return 0;
}
