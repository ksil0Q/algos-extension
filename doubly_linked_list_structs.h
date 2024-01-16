#include <Python.h>


typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    PyObject_HEAD
    struct Node* head;
    struct Node* tail;
    struct Node* iter_current;
} DoublyLinkedList;

#define DOUBLY_LINKED_LIST_STRUCTS