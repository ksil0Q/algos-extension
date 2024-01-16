#include <Python.h>
#ifndef DOUBLY_LINKED_LIST_STRUCTS
#include "doubly_linked_list_structs.h"
#endif
#include "doubly_linked_list_methods.h"


static PyObject* insertAtFrontEx(DoublyLinkedList* self, PyObject* args) {
    int item;
    
    if (!PyArg_ParseTuple(args, "i", &item))
    {
        PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        return NULL;
    }
    
    insertAtFront(self, item);
    Py_RETURN_NONE;
};

static PyObject* insertAtBackEx(DoublyLinkedList* self, PyObject* args) {
    int item;
    
    if (!PyArg_ParseTuple(args, "i", &item))
    {
        PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        return NULL;
    }
    
    insertAtBack(self, item);
    Py_RETURN_NONE;
};

static PyObject* insertAfterEx(DoublyLinkedList* self, PyObject* args) {
    int key;
    int item;
    
    if (!PyArg_ParseTuple(args, "ii", &key, &item))
    {
        PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        return NULL;
    }
    
    if (insertAfter(self, key, item) < 0)
        return NULL;
    
    Py_RETURN_TRUE;
};

static PyObject* popBackEx(DoublyLinkedList* self, PyObject* Py_UNUSED(ignored)) {    
    int item = popBack(self);

    if (PyErr_Occurred())
        return NULL;

    return Py_BuildValue("i", item);
};

static PyObject* popFrontEx(DoublyLinkedList* self, PyObject* Py_UNUSED(ignored)) {    
    int item = popFront(self);

    if (PyErr_Occurred())
        return NULL;
    
    return Py_BuildValue("i", item);
};

static PyObject* deleteEx(DoublyLinkedList* self, PyObject* args) 
{ 
    int key;
    
    if (!PyArg_ParseTuple(args, "i", &key))
    {
        PyErr_SetString(PyExc_TypeError, "key must be integer");
        return NULL;
    }
    
    if (delete_item(self, key))
        Py_RETURN_NONE;
    
    return NULL;
};

static void DoublyLinkedList_dealloc(DoublyLinkedList* self)
{
    Py_XDECREF(self->head);
    Py_XDECREF(self->tail);
    Py_XDECREF(self->iter_current);

    Py_TYPE(self)->tp_free((PyObject*) self);
};

static int DoublyLinkedList_init(DoublyLinkedList* self, PyObject* args)
{
    PyObject* list;
    Py_ssize_t list_len;
    PyObject* list_item;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &list))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list");
        return -1;
    }

    list_len = PyList_Size(list);
    for (int i = 0; i < list_len; i++)
    {
        list_item = PyList_GetItem(list, i);
        
        if (!PyLong_Check(list_item))
        {
            PyErr_SetString(PyExc_TypeError, "list items must be integers.");
            return -1;
        }
        int converted_list_item;

        if (!PyArg_Parse(list_item, "i", &converted_list_item))
            return -1;

        insertAtBack(self, converted_list_item);

    }
    self->iter_current = self->head;
    return 0;
};

PyObject* DoublyLinkedList_iter(PyObject* pself)
{
    DoublyLinkedList* self = (DoublyLinkedList*)pself;
    self->iter_current = self->head; 
    
    Py_INCREF(pself);
    return pself;
};

PyObject* DoublyLinkedList_iternext(PyObject* pself)
{
    DoublyLinkedList* self = (DoublyLinkedList*) pself;

    if (self->iter_current != NULL)
    {
        PyObject* current_val = Py_BuildValue("i", self->iter_current->data);
        self->iter_current = self->iter_current->next;
        return current_val;
    }
    else 
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
};

static PyMethodDef DoublyLinkedList_methods[] = {
    {"append", (PyCFunction) insertAtBackEx, METH_VARARGS,
        "insert value at the end of the linked list"
    },
    {"append_left", (PyCFunction) insertAtFrontEx, METH_VARARGS,
        "insert value at the end of the linked list"
    },
    {"insert", (PyCFunction) insertAfterEx, METH_VARARGS, 
        "insert value after key-element"
    },
    {"pop_tail", (PyCFunction) popBackEx, METH_NOARGS,
        "pop the last value from the list"
    },
    {"pop_head", (PyCFunction) popFrontEx, METH_NOARGS,
        "pop the first value from the list"
    },
    {"delete", (PyCFunction) deleteEx, METH_VARARGS,
        "delete element by it`s value"
    },
    {NULL}  
};

static PyObject* DoublyLinkedList_gethead(DoublyLinkedList *self, void *closure)
{
    return Py_BuildValue("i", self->head->data);
};

static PyObject* DoublyLinkedList_gettail(DoublyLinkedList *self, void *closure)
{
    return Py_BuildValue("i", self->tail->data);
};

static PyGetSetDef DoublyLinkedList_getsetters[] = {
    {"head", (getter) DoublyLinkedList_gethead, NULL,
     "head of linked list", NULL},
    {"tail", (getter) DoublyLinkedList_gettail, NULL,
     "tail of linked list", NULL},
    {NULL}  /* Sentinel */
};

PyTypeObject DoublyLinkedListEx = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "DoublyLinkedList",
    .tp_doc = "A DoublyLinkedList is a linear data structure where each node has a link to the next node as well as to the previous node.",
    .tp_basicsize = sizeof(DoublyLinkedList),
    .tp_itemsize = 0, 
    .tp_flags = Py_TPFLAGS_DEFAULT, 
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)DoublyLinkedList_init,
    .tp_dealloc = (destructor)DoublyLinkedList_dealloc,
    .tp_getset = DoublyLinkedList_getsetters,
    .tp_methods = DoublyLinkedList_methods,
    .tp_iter = (getiterfunc)DoublyLinkedList_iter,
    .tp_iternext = (iternextfunc)DoublyLinkedList_iternext
};