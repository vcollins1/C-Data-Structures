#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

void printInt(const void* a) {
    printf("%d", *(int*)a);
}

int main(void) {
    printf("Data Structures Implementation using the c programming language\n");
    vec_t* vec = createVec(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90;
    pushBack(vec, &a);

    pushBack(vec, &b);

    pushBack(vec, &c);

    pushBack(vec, &d);
    printVec(vec, printInt);

    destroyVec(vec, NULL);
    return 0;
}
