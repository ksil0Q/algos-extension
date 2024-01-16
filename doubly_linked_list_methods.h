#ifndef DOUBLY_LINKED_LIST_STRUCTS
#include "doubly_linked_list_structs.h"
#endif


void insertAtFront(DoublyLinkedList* self, int value);
void insertAtBack(DoublyLinkedList* self, int value);
int insertAfter(DoublyLinkedList* self, int key, int value);
int popBack(DoublyLinkedList* self);
int popFront(DoublyLinkedList* self);
int delete_item(DoublyLinkedList* self, int key);