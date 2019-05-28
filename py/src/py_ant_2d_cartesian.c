#include <stdio.h>
#include "py_ant_2d_cartesian.h"
#include "antmacro.h"

/* SETTERS */

int ant_2d_cart_set_position(py_ant * self, PyTupleObject * value, void * closure)
{

	#ifdef LIBANT_DEBUG
	puts(DEBUG("Setting 2D Cartesian Ant position..."));
	#endif
	
	if (value == NULL)
	{
		
		//zero-fill the tuple and maintain its size
		#ifdef LIBANT_DEBUG
		puts(DEBUG("Attempting to zero internal position array..."));
		#endif
		self->ant = zero_ant_position(self->ant, 2);
		return 0;
		
	}
	else if(!PyTuple_Check(value))
	{
		
		//Invalid type - not a tuple
		PyErr_SetString(PyExc_TypeError, "Position value should be a duple for a 2D Cartesian Ant.");
		return -1;
		
	}
	else if (PyTuple_GET_SIZE(value) != 2)
	{
		
		//Tuple is not correct size
		PyErr_SetString(PyExc_ValueError, "Position value must be a duple (tuple of size 2).");
		return -1;
		
	}
	
	return ant_set_position(self, value, closure);

}

int ant_2d_cart_set_orientation(py_ant * self, PyObject * value, void * closure)
{

	if (!PyLong_Check(value))
	{

		//Invalid type - not an integer
		PyErr_SetString(PyExc_TypeError, "Value should be an unsigned long.");
		return -1;

	}


	unsigned long long_value = PyLong_AsUnsignedLong(value);

	if (long_value == -1 || long_value > 4294967295) //TODO this bound is really weird and not acting right, also using same value is overflow on windows
	{

		#ifdef LIBANT_DEBUG
		puts(DEBUG("Error in getting unsigned long from orientation value."));
		#endif
		
		PyErr_SetString(PyExc_ValueError, "Invalid value for orientation. Value should be unsigned and less than or equal to 4294967295."); // ULONG_MAX aka " xstr(UINT_MAX) ".");
		return -1;

	}

	#ifdef LIBANT_DEBUG
	printf(DEBUG("Setting Ant position with unsigned long value of %ld...")"\n", long_value);
	#endif

	self->ant->orientation = long_value;


	return 0;

}

/* END SETTERS */

#ifndef _WIN32
static
#endif
PyGetSetDef ant_2d_cart_getsetters[] = {

	{"position", (getter) ant_get_position, (setter) ant_2d_cart_set_position, "ant position", NULL},
	{"orientation", (getter) ant_get_orientation, (setter) ant_set_orientation, "ant orientation", NULL},  
	{NULL}

};

PyTypeObject py_ant_2d_cartesian_type = {
	
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "libant.Ant2DCartesian",
    .tp_doc = "2D ant",
    .tp_basicsize = sizeof(py_ant),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_getset = ant_2d_cart_getsetters,
		
};
