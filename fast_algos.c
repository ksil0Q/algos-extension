#include <Python.h>

#include "karatsuba.h"
#include "knuth_morris_pratt.h"
#include "doubly_linked_list.h"

static PyMethodDef FastAlgosMethods[] = {
    {"karatsuba", karatsuba_ex, METH_VARARGS, "Karatsuba method for multiply large nums"},
    {"knuth_morris_pratt", knuth_morris_pratt_ex, METH_VARARGS, "Knuth-Morris-Pratt algorithm for searching for a pattern in the text"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef FastAlgos =
{
    PyModuleDef_HEAD_INIT,
    "fast_algos",
    "Fast algos & structures for Python from C",
    -1,
    FastAlgosMethods
};


PyMODINIT_FUNC PyInit_FastAlgos(void)
{
    PyObject* module;

    if (!PyType_Ready(&DoublyLinkedListEx) < 0)
        return NULL;
    
    module = PyModule_Create(&FastAlgos);
    if (module == NULL)
        return NULL;

    Py_INCREF(&DoublyLinkedListEx);
    if (PyModule_AddObject(module, "DLL", (PyObject*) &DoublyLinkedListEx) < 0)
    {
        Py_DECREF(&DoublyLinkedListEx);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}
