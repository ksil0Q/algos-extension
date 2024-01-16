#include <Python.h>
#include <stdlib.h>


#define MIN_LENGTH_FOR_KARATTSUBA 100000
#define MAX(X, Y) (((X) >= (Y)) ? (X) : (Y))


static long long karatsuba(long long first, long long second)
{
    if (first == 0 || second == 0)
        return 0;

    if(first < MIN_LENGTH_FOR_KARATTSUBA  || second < MIN_LENGTH_FOR_KARATTSUBA)
        return first * second;
    else
    {
        int first_digits = (int)floor(log10(abs(first))) + 1;
        int second_digits = (int)floor(log10(abs(second))) + 1;

        int max = MAX(first_digits, second_digits);
        int n_2 = (max % 2 != 0) ? max / 2 + 1 : max / 2;

        long degree = pow(10, n_2);

        long long a = first / degree;
        long long b = first % degree;

        long long c = second / degree;
        long long d = second % degree;
        
        long long ac = karatsuba(a, c);
        long long bd = karatsuba(b, d);

        return ac * pow(10, max) + (karatsuba(a + b, c + d) - ac - bd) * degree + bd;

    }    
}

PyObject* karatsuba_ex(PyObject* self, PyObject* args){
    long long first;
    long long second;
    
    if (!PyArg_ParseTuple(args, "LL", &first, &second))
    {
        PyErr_SetString(PyExc_TypeError, "arguments must be integers");
        return NULL;
    }
    long long result = karatsuba(first, second);

    return Py_BuildValue("L", result);
}
