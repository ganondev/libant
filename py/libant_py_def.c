#include <stdio.h>
#include "libant_py_def.h"

PyTupleObject * ant_get_position(py_ant * self, void * closure)
{

	#ifdef PY_DEBUG
	puts("Get Ant position");
	#endif
	PyTupleObject * position_tuple = (PyTupleObject *) PyTuple_New(3);
	Py_INCREF(position_tuple);
	return position_tuple;

}

int ant_set_position(py_ant * self, PyObject * value, void * closure)
{

	#ifdef PY_DEBUG
	puts("Set Ant position");
	#endif

	PyTupleObject * tmp;
	if (value == NULL) //position is being deleted, set to zeros
	{
		//TODO zero the tuple
		Py_ssize_t tuple_size = (long int) sizeof(self->ant.position);
		printf("%ld", tuple_size);
		value = (PyTupleObject *) PyTuple_Pack(tuple_size, PyLong_FromLong(0));
		
	}
	//TODO otherwise just use the size of value

	return 0;

}

PyObject * ant_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

    py_ant * self = (py_ant *) type->tp_alloc(type, 0);
    if (self != NULL)
    {

	#ifdef PY_DEBUG
        puts("Got a new Ant!");
	#endif

    }

    return (PyObject *) self;

}

int ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

    //static char * kwlist[] = {"test", NULL};
    //if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &self->test)) return -1;
	//TODO TAKE TUPLE AS POSITION ARGUMENT, DEFAULTS TO (0,0)
    return 0;

}

void ant_dealloc(py_ant * self)
{

    Py_TYPE(self)->tp_free((PyObject *) self);

}

PyMODINIT_FUNC PyInit_libant(void)
{

    PyObject *m;
    if (PyType_Ready(&py_ant_type) < 0) return NULL;

    m = PyModule_Create(&libant);
    if (m == NULL) return NULL;

    Py_INCREF(&py_ant_type);
    PyModule_AddObject(m, "Ant", (PyObject *) &py_ant_type);
    return m;

}

void zero_ant_position(py_ant * ant, Py_ssize_t size, bool allocated)
{

	if (allocated) free(ant->ant.position);
	ant->ant.position = calloc((size_t) size, sizeof(int));
	//TODO figure out how to support any sized tuple 
	PyObject * zero = PyLong_FromLong(0);
	PyTupleObject * value = (PyTupleObject *) PyTuple_Pack(size, zero, zero, zero);

}
