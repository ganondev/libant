#include "libant_py_def.h"

PyObject * ant_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

    py_ant * self = (py_ant *) type->tp_alloc(type, 0);
    if (self != NULL)
    {

        self->test = 1231;

    }

    return (PyObject *) self;

}

int ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

    static char * kwlist[] = {"test", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &self->test)) return -1;
    return 0;

}

void ant_dealloc(py_ant * self)
{

    Py_TYPE(self)->tp_free((PyObject *) self);

}

PyMODINIT_FUNC PyInit_libant(void)
{

    PyObject *m;
    if (PyType_Ready(&py_ant_type) < 0)
    return NULL;

    m = PyModule_Create(&libant);
    if (m == NULL)
    return NULL;

    Py_INCREF(&py_ant_type);
    PyModule_AddObject(m, "Ant", (PyObject *) &py_ant_type);
    return m;

}
