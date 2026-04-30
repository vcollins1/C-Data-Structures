#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

// List data types
typedef struct List list_t;
typedef struct ListIterator listIter_t;

// List callback functions types
typedef void (*printCallback)(const void* data);
typedef void (*clearCallback)(void* data);
typedef bool (*findCallback)(void* a, void* key);

// List status and error codes
typedef enum {
    ListOperationSuccess = 0,
    ListRemoveError,
    ListMemoryError,
    ListIndexError,
    ListEmptyError,
    ListNotFoundError,
} ListStatusCode;

// Create and Destory List functions
list_t* createList(int dataSize);
void destroyList(list_t* list, clearCallback func);

// Add elements to list
ListStatusCode unshift(list_t* list, void* data);
ListStatusCode addBack(list_t* list, void* data);
ListStatusCode insertAt(list_t* list, size_t index, void* data);

// Remove elements from the list
ListStatusCode shift(list_t* list, void* output);
ListStatusCode removeBack(list_t* list, void* output);
ListStatusCode removeAt(list_t* list, size_t index, void* output);

// Utility functions
void clearList(list_t* list, clearCallback func);
size_t listSize(list_t* list);
bool isListEmpty(list_t* list);
ListStatusCode find(list_t* list, void* key, void* found, findCallback func);
ListStatusCode set(list_t* list, size_t index, void* update);

// List iteratoion
listIter_t* createListIterator(list_t* list);
void listIteratorNext(listIter_t* iter);
void getListIteratorData(listIter_t* iter, void* output);
bool hasNext(listIter_t* iter);

// Display elements of list
void printList(list_t* list, printCallback func);

#endif
