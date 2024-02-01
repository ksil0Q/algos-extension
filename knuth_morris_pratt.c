#include <Python.h>
// #include "memwatch.h"


int* get_prefix_f(char* pattern)
{
    size_t prefix_len = strlen(pattern);
    int* prefix_fun = calloc(prefix_len, sizeof(int));

    int k = 0;

    for (int q = 2; q < prefix_len; q++)
    {
        while (k > 0 && pattern[k + 1] != pattern[q])
            k = prefix_fun[k];

        if (pattern[k + 1] == pattern[q])
            k += 1;
        
        prefix_fun[q] = k;
    }

    return prefix_fun;
}

int knuth_morris_pratt(char* text, char* pattern)
{
    size_t text_len = strlen(text);
    size_t pattern_len = strlen(pattern);

    int* prefix_fun = get_prefix_f(pattern);

    char* new_pattern = (char*)malloc(pattern_len + 2);
    new_pattern[0] = '-';
    strcpy(new_pattern + 1, pattern);

    char* new_text = (char*)malloc(text_len + 2);
    new_text[0] = '-';
    strcpy(new_text + 1, text);

    int q = 0;
    int res_index = -1;

    for (int i = 1; i < text_len + 1; i++)
    {
        while (q > 0 && new_pattern[q + 1] != new_text[i])
            q = prefix_fun[q];

        if (new_pattern[q + 1] == new_text[i])
            q += 1;

        if (q == pattern_len)
        {
            res_index = i - (int)pattern_len;
            break;
        }
    }

    free(prefix_fun);
    free(new_pattern);
    free(new_text);
    
    return res_index;
}

PyObject* knuth_morris_pratt_ex(PyObject* self, PyObject* args)
{
    char* text;
    char* pattern;

    if (!PyArg_ParseTuple(args, "ss", &text, &pattern))
    {
        PyErr_SetString(PyExc_TypeError, "arguments must be strings");
        return NULL;
    }
    int result = - 1;

    Py_BEGIN_ALLOW_THREADS // release GIL before computations

    result = knuth_morris_pratt(text, pattern);

    free(text);
    free(pattern); // free memory before GIL acquiring

    Py_END_ALLOW_THREADS // reacquire GIL
    

    if (result < 0)
    {
        PyErr_SetString(PyExc_ValueError, "no given substring in text");
        return NULL;
    }

    return Py_BuildValue("i", result);
}


// int main()
// {
//     int result = knuth_morris_pratt("asrnaocvepromgoismweroingxkzmfepojgeposdlfv", "weroing");
//     return 0;
// }