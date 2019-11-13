#include <stdio.h>
#include <py_ant3.h>

/* GETTERS */

PyLongObject * ant3_get_z(py_ant * self, void * closure)
{

	#ifdef LIBANT_DEBUG
	puts(DEBUG("Getting Ant position z value..."));
	#endif

	PyObject * z = position_as_py_long(core_ant(self), 2);
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
		zero_ant_position(core_ant(self));
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
		core_ant(self)->position[2] = 0;
		return 0;
		
	}
	else if(!PyLong_Check(value))
	{
		
		//Invalid type - not an int
		PyErr_SetString(PyExc_TypeError, "Position values should be signed integers.");
		return -1;
		
	}
	
	core_ant(self)->position[2] = PyLong_AsLongLong((PyObject *) value);
	
	return 0;
	
}

/* END SETTERS */

PyObject * ant3_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

	py_ant * self = ant_alloc(type, 3);
    if (self != NULL)
    {

		LOG(puts(DEBUG("Got a new 3D Ant!")));

	}

    return (PyObject *) self; //TODO is NULL when None is passed to constructor
}

int ant3_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	ant_init(self, args, kwargs);
	core_ant(self)->tuple_size = 3;
	core_ant(self)->position[0] = 0;
	core_ant(self)->position[1] = 0;
	core_ant(self)->position[2] = 0;
	
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
	.tp_new = ant3_new,
	.tp_init = (initproc) ant3_init,
	
};
