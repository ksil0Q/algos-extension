#ifndef DOUBLY_LINKED_LIST_STRUCTS
#include "doubly_linked_list_structs.h"
#endif


static int isEmpty(DoublyLinkedList* self) 
{
    return self->head == NULL;
};

void insertAtFront(DoublyLinkedList* self, int value)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    
    if (isEmpty(self)) {
        self->head = node;
        self->tail = node;
    } else {
        node->next = self->head;
        self->head->prev = node;
        self->head = node;
    }
};

void insertAtBack(DoublyLinkedList* self, int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    
    if (isEmpty(self)) {
        self->head = node;
        self->tail = node;
    } else {
        self->tail->next = node;
        node->prev = self->tail;
        self->tail = node;
    }
};

int insertAfter(DoublyLinkedList* self, int key, int value)
{
    Node* node = malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;

    
    Node* currentNode = self->head;
    while (currentNode != NULL && currentNode->data != key)
        currentNode = currentNode->next;
    
    if (currentNode == NULL) {
        PyErr_SetString(PyExc_IndexError, "element not found");
        return -1;
    } else if (currentNode->next == NULL) {
        currentNode->next = node;
        node->prev = currentNode;
        self->tail = node;
    } else {
        Node* nextPtr = currentNode->next;
        currentNode->next = node;
        node->prev = currentNode;
        node->next = nextPtr;
        nextPtr->prev = node;
    }

    return 1;
};

int popBack(DoublyLinkedList* self)
{
    int item;
    if (isEmpty(self))
    {
        PyErr_SetString(PyExc_IndexError, "pop from empty linked list");
        return -1;
    }
    else
    {
        item = self->tail->data;

        if (self->tail->prev != NULL)
            self->tail->prev->next = NULL;
        
        Node* prev = self->tail->prev;
        self->head->prev = NULL;
        free(self->tail);
        self->tail = prev;

    } 
    
    return item;
};

int popFront(DoublyLinkedList* self)
{
    int item;
    if (isEmpty(self)) {
        PyErr_SetString(PyExc_IndexError, "pop from empty linked list");
        return -1;
    } else {
        item = self->head->data;
        if (self->head->next != NULL) {
            self->head->next->prev = NULL;
        }
        Node* next = self->head->next;
        free(self->head);
        self->head = next;
    }
    
    return item;
};

int delete_item(DoublyLinkedList* self, int key)
{
    if (isEmpty(self)) {
        PyErr_SetString(PyExc_IndexError, "delete from empty linked list");
        return -1;
    }
    
    Node* currPtr = self->head;
    while(currPtr != NULL && currPtr->data != key) {
        currPtr = currPtr->next;
    }
    
    if (currPtr == NULL) {
        PyErr_SetString(PyExc_IndexError, "element not found");
        return -1;
    }
    
    if (currPtr->prev == NULL) {
        return popFront(self);

    } else if (currPtr->next == NULL) {
        return popBack(self);

    } else {
        Node* nextPtr = currPtr->next;
        Node* prevPtr = currPtr->prev;
        nextPtr->prev = prevPtr;
        prevPtr->next = nextPtr;
        currPtr->next = NULL;
        currPtr->prev = NULL;
        free(currPtr);
        currPtr = NULL;
    }

    return 1;
};