#include <Python.h>

#include "mblas_core.h"

static PyObject *mblas_error = NULL;

static PyObject *mblas_version(PyObject *self) {
    return Py_BuildValue("s", "MBLAS version 0.1");
}

// Python wrapper for the sgemm C function
static PyObject *sgemm_c(PyObject *self, PyObject *args) {
    Py_buffer view1, view2, view3;
    PyObject *obj1 = NULL, *obj2 = NULL, *obj3 = NULL;
    u64 n = 0;

    // Get the parameter (expected: three 1-dimensional arrays of float and an u64)
    if (!PyArg_ParseTuple(args, "OOOK", &obj1, &obj2, &obj3, &n)) {
        return NULL;
    }

    // Get the array memory view
    if (PyObject_GetBuffer(obj1, &view1, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1) {
        return NULL;
    }

    if (PyObject_GetBuffer(obj2, &view2, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1) {
        return NULL;
    }

    if (PyObject_GetBuffer(obj3, &view3, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1) {
        return NULL;
    }

    if (view1.ndim != 1 || view2.ndim != 1 || view3.ndim != 1) {
        PyErr_SetString(PyExc_TypeError, "expecting three 1-dimensional arrays");
        PyBuffer_Release(&view1);
        PyBuffer_Release(&view2);
        PyBuffer_Release(&view3);
        return NULL;
    }

    if (strcmp(view1.format, "f") || strcmp(view2.format, "f") || strcmp(view3.format, "f")) {
        PyErr_SetString(PyExc_TypeError, "expecting three 1-dimensional arrays of floats");
        PyBuffer_Release(&view1);
        PyBuffer_Release(&view2);
        PyBuffer_Release(&view3);
        return NULL;
    }
  
    if (view1.shape[0] != view2.shape[0] || view1.shape[0] != view3.shape[0]) {
        PyErr_SetString(
            PyExc_TypeError,
            "expecting three 1-dimensional arrays of the same size"
        );
        PyBuffer_Release(&view1);
        PyBuffer_Release(&view2);
        PyBuffer_Release(&view3);
        return NULL;     
    }

    sgemm(view1.buf, view2.buf, view3.buf, n);

    // Return the C function's return value as a Python float object 
    return Py_BuildValue("i", 0);
}

// Register the methods to be made available Python side
static PyMethodDef mblas_methods[] = {
  { "sgemm_c",      sgemm_c,      METH_VARARGS, "Returns the result of single precision matrix multiplication."},
  // { "sgemm_AVX",    sgemm_AVX,    METH_VARARGS, "Returns the result of single precision matrix multiplication (optimized for x86 with AVX)."},
  // { "sgemm_AVX512", sgemm_AVX512, METH_VARARGS, "Returns the result of single precision matrix multiplication (optimized for x86 with AVX512)."},
  { "version", (PyCFunction)mblas_version, METH_VARARGS, "Returns the version of the MBLAS library." },
  { NULL, NULL, 0, NULL}
};

static PyModuleDef mblas_module = {
    PyModuleDef_HEAD_INIT,
    "MBLAS",
    "MBLAS library",
    -1,
    mblas_methods
};

PyMODINIT_FUNC PyInit_mblas() {
    PyObject *obj = PyModule_Create(&mblas_module);

    if (!obj) {
        return NULL;
    }

    mblas_error = PyErr_NewException("mblas.error", NULL, NULL);
    Py_XINCREF(mblas_error);
  
    if (PyModule_AddObject(obj, "error", mblas_error) < 0) {
        Py_XDECREF(mblas_error);
        Py_CLEAR(mblas_error);
        Py_DECREF(obj);
        return NULL;
    }

    return obj;
}
