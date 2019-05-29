#include <stdio.h>
#include "py_ant3.h"
#include "antmacro.h"

/* GETTERS */

PyLongObject * ant3_get_z(py_ant * self, void * closure)
{

	#ifdef LIBANT_DEBUG
	puts(DEBUG("Getting Ant position z value..."));
	#endif

	PyObject * z = position_as_py_long(self->ant, 2);
	Py_INCREF(z);
	return (PyLongObject *) z;

}

/* SETTERS */

int ant3_set_position(py_ant * self, PyTupleObject * value, void * closure)
{

	#ifdef LIBANT_DEBUG
	puts(DEBUG("Setting Ant3 triple position..."));
	#endif
	
	if (value == NULL)
	{
		
		//zero-fill the tuple and maintain its size
		#ifdef LIBANT_DEBUG
		puts(DEBUG("Attempting to zero internal position array..."));
		#endif
		zero_ant_position(self->ant);
		return 0;
		
	}
	else if(!PyTuple_Check(value))
	{
		
		//Invalid type - not a tuple
		PyErr_SetString(PyExc_TypeError, "Position value should be a duple for an Ant2 instance.");
		return -1;
		
	}
	else if (PyTuple_GET_SIZE(value) != 3)
	{
		
		//Tuple is not correct size
		PyErr_SetString(PyExc_ValueError, "Position value must be a triple (tuple of size 3).");
		return -1;
		
	}
	
	return ant_set_position(self, value, closure);

}

int ant3_set_z(py_ant * self, PyLongObject * value, void * closure)
{
	
	#ifdef LIBANT_DEBUG
	puts(DEBUG("Setting Ant position z value..."));
	#endif
	
	if (value == NULL)
	{
		
		#ifdef LIBANT_DEBUG
		puts(DEBUG("Setting z to zero in lieu of deletion..."));
		#endif
		self->ant->position[2] = 0;
		return 0;
		
	}
	else if(!PyLong_Check(value))
	{
		
		//Invalid type - not an int
		PyErr_SetString(PyExc_TypeError, "Position values should be signed integers.");
		return -1;
		
	}
	
	self->ant->position[2] = PyLong_AsLongLong((PyObject *) value);
	
	return 0;
	
}

/* END SETTERS */

int ant3_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

    //static char * kwlist[] = {"test", NULL};
    //if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &self->test)) return -1;
	//TODO TAKE TUPLE AS POSITION ARGUMENT, DEFAULTS TO (0,0)
	
	self->ant = create_ant(3);
	
    return 0;

}

#ifndef _WIN32
static
#endif
PyGetSetDef ant3_getsetters[] = {

	{"position", (getter) ant_get_position, (setter) ant3_set_position, "ant position", NULL},
	{"z", (getter) ant3_get_z, (setter) ant3_set_z, "ant position", NULL},
	{NULL}

};

PyTypeObject py_ant3_type = {
	
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.Ant3",
	.tp_doc = "3D ant",
	.tp_basicsize = sizeof(py_ant),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_getset = ant3_getsetters,
	.tp_init = (initproc) ant3_init,
	
};
