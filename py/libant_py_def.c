#include <stdio.h>
#include "libant_py_def.h"

PyTupleObject * ant_get_position(py_ant * self, void * closure)
{

	#ifdef PY_DEBUG
	puts(DEBUG("Getting Ant position..."));
	#endif
	size_t size = self->ant->tuple_size;
	PyObject * position_tuple = PyTuple_New(size);
	#ifdef PY_DEBUG
	printf(DEBUG("Size of tuple: %ld")"\n", size);
	#endif
	for (int i = 0; i < size; i++)
	{
			
		PyTuple_SetItem(position_tuple, i, PyLong_FromLongLong(self->ant->pos[i]));
		
	}
	Py_INCREF(position_tuple);
	return (PyTupleObject *) position_tuple;

}

int ant_set_position(py_ant * self, PyTupleObject * value, void * closure)
{

	#ifdef PY_DEBUG
	puts(DEBUG("Setting Ant position..."));
	#endif
	
	size_t stored_tuple_size = self->ant->tuple_size;
	if (value == NULL)
	{
		
		//zero-fill the tuple and maintain its size
		#ifdef PY_DEBUG
		puts(DEBUG("Attempting to zero internal position array..."));
		#endif
		self->ant = zero_ant_position(self->ant, stored_tuple_size, true);
		return 0;
		
	}
	else if(!PyTuple_Check(value))
	{
		
		//Invalid type - not a tuple
		PyErr_SetString(PyExc_TypeError, "Position value should be a tuple.");
		return -1;
		
	}
	
	size_t incoming_tuple_size = PyTuple_GET_SIZE(value);
	PyObject * tuple_values[incoming_tuple_size];
	for (int i = 0; i < incoming_tuple_size; i++)
	{

		//Retreive value from tuple
		PyObject * tuple_member = PyTuple_GET_ITEM(value, (Py_ssize_t) i); 
		//Assert that tuple member is a python integer
		if (!PyLong_Check(tuple_member))
		{

			//Invalid type - not an integer
			PyErr_SetString(PyExc_TypeError, "Tuple value should be an integer.");
			return -1;

		}

		tuple_values[i] = tuple_member;

	}

	if (incoming_tuple_size != stored_tuple_size)
	{
		
		#ifdef PY_DEBUG
		printf(DEBUG("Resizing internal position tuple to size %ld...")"\n", incoming_tuple_size);
		#endif
		
		self->ant = zero_ant_position(self->ant, incoming_tuple_size, true);
		
	}

	for (int i = 0; i < incoming_tuple_size; i++)
	{
		
		//Evaluate long long int value of tuple member
		long long int int_value = PyLong_AsLongLong(tuple_values[i]);
		self->ant->pos[i] = int_value;

	}

	return 0;

}

PyObject * ant_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

    py_ant * self = (py_ant *) type->tp_alloc(type, 0);
    if (self != NULL)
    {

	#ifdef PY_DEBUG
        puts(DEBUG("Got a new Ant!"));
	#endif

    }

    return (PyObject *) self;

}

int ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

    //static char * kwlist[] = {"test", NULL};
    //if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &self->test)) return -1;
	//TODO TAKE TUPLE AS POSITION ARGUMENT, DEFAULTS TO (0,0)
	
	self->ant = zero_ant_position(self->ant, 5, false);
	
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
