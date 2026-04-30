#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void printInt(const void* data) {
    printf("%d", *(int*)data);
}

// bool findInt(void* data, void* key) {
//     return *(int*)data == *(int*)key;
// }

int main(void) {
    list_t* list = createList(sizeof(int));

    int a = 1, b = 2, c = 3;
    unshift(list, &a);
    unshift(list, &b);
    unshift(list, &c);
    printList(list, printInt);

    void* data = malloc(sizeof(int));

    listIter_t* iter = createListIterator(list);
    
    while (hasNext(iter)) {
        getListIteratorData(iter, data);
        printf("%d ", *(int*)data);
        listIteratorNext(iter);
    }
    printf("\n");
    destroyListIterator(iter);

    destroyList(list, NULL);
    free(data);
    return 0;
}
