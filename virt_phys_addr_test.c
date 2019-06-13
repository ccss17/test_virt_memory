#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libkdump.h"

void strtest(void) {
    char *s;

    s = strdup("Holberton");
    if (s == NULL)
    {
        fprintf(stderr, "Can't allocate mem with malloc\n");
        return;
    }
    printf("%p\n", (void *)s);
}

int main(void) {
    int * test;
    int test2;
    test = (int *)malloc(sizeof(int));
    printf("%p\n", test);
    printf("%p\n", &test);
    printf("%p\n", &test2);
    printf("%p\n", libkdump_virt_to_phys((size_t)test));
    strtest();
    pause();
    return 0;
}
