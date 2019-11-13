#ifdef LIBANT_DEBUG
#include <stdio.h>
#endif

#include <antmacro.h>
#include <libant_py_ant.h>
#include <libant_grid.h>

/* GENERAL METHODS */

//TODO general position checker

void ant_t_directive_wrapper(ant_t * ant, ant_grid_t * grid)
{

	LOG(puts("Attempting to exeucte wrapped python directive for ant %s."));

	// Expect ant to be embedded into a py_ant structure
	py_ant * pyobj = container_of(ant, py_ant, ant);

	// LAST LEFT OFF HERE 11/13/2019 12:25 AM

}

PyObject * langtons_ant_default_directive_wrapper(PyObject * module, PyObject * args)
{
	
	PyObject * arg_ant, * grid;

	if (PyArg_UnpackTuple(args, "langtons_ant_directive", 2, 2, &arg_ant, &grid))
	{

		if (!py_ant_check(arg_ant))
		{

			PyErr_SetString(PyExc_TypeError, "First argument should be of type Ant.");
			return NULL;

		}
		if (!py_grid_check(grid))
		{
			
			PyErr_SetString(PyExc_TypeError, "Second argument should be of type Grid.");

		}

		py_ant * ant = (py_ant *)arg_ant;

		Py_INCREF(ant);
		Py_INCREF(grid);

		if (core_ant(ant)->orientation < 0 || core_ant(ant)->orientation > 3)
		{

			PyErr_SetString(PyExc_IndexError, "Langton's ant has only four valid orientations. Orientation field should be valued between 0 and 3.");
			Py_DECREF(ant);
			Py_DECREF(grid);
			return NULL;

		}

		langtons_ant_default_directive(core_ant(ant), ((py_grid *)grid)->grid);

		Py_DECREF(ant);
		Py_DECREF(grid);

		Py_RETURN_NONE;

	}

	#ifdef LIBANT_DEBUG
	puts(ERROR("Argument parsing failed."));
	#endif

	if (!PyErr_Occurred()) PyErr_SetString(PyExc_Exception, "Arguments could not be parsed."); //TODO this needs to be specified

	return NULL;
	
}

PyMethodDef langtons_ant_directive = {"langtons_ant_directive", (PyCFunction) langtons_ant_default_directive_wrapper, METH_VARARGS, "Default directive for langton's ant." };

PyFunctionObject * langtons_ant_directive_func = NULL;

/* END GENERALS */

/* GETTERS */
PyTupleObject * ant_get_position(py_ant * self, void * closure)
{

	LOG(puts(DEBUG("Getting Ant position...")));

	size_t size = self->ant.tuple_size;
	PyObject * position_tuple = PyTuple_New(size);

	LOG(printf(DEBUGLN("Size of tuple: %zu"), size));

	for (int i = 0; i < size; i++)
	{
			
		PyTuple_SetItem(position_tuple,
						i,
						position_as_py_long(core_ant(self), i));
		
	}
	Py_INCREF(position_tuple);
	return (PyTupleObject *) position_tuple;

}

PyLongObject * ant_get_orientation(py_ant * self, void * closure)
{

	LOG(puts(DEBUG("Getting Ant orientation...")));

	PyObject * orientation = PyLong_FromUnsignedLong(core_ant(self)->orientation);
	Py_INCREF(orientation);
	return (PyLongObject *) orientation;

}

PyFunctionObject * ant_get_directive(py_ant * self, void * closure) //TODO PyMethodObject
{

	return self->py_directive;
	
}

/* END GETTERS */

/* SETTERS */

int ant_set_position(py_ant * self, PyTupleObject * value, void * closure)
{

	LOG(puts(DEBUG("Setting Ant position...")));
	
	size_t stored_tuple_size = core_ant(self)->tuple_size;
	if (value == NULL)
	{
		
		//zero-fill the tuple and maintain its size
		LOG(puts(DEBUG("Attempting to zero internal position array...")));
		zero_ant_position(core_ant(self));
		return 0;
		
	}
	else if(!PyTuple_Check(value))
	{
		
		//Invalid type - not a tuple
		PyErr_SetString(PyExc_TypeError, "Position value should be a tuple.");
		return -1;
		
	}
	
	size_t incoming_tuple_size = PyTuple_GET_SIZE(value);
	#ifndef _WIN32
	PyObject * tuple_values[incoming_tuple_size];
	#else
	//TODO free
	PyObject ** tuple_values = malloc(sizeof(PyObject *) * incoming_tuple_size);
	#endif
	
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
		
		LOG(printf(DEBUGLN("Resizing internal position tuple to size %zu..."), incoming_tuple_size));
		LOG(puts(ERRORLN("TODO resizing the ant position requires resizing the entire ant, which is currently broken because the core ant has been inlined")));
		
		//self->ant = resize_ant_position(self->ant, incoming_tuple_size);
		
	}

	for (int i = 0; i < incoming_tuple_size; i++)
	{
		
		//Evaluate long long int value of tuple member
		long long int int_value = PyLong_AsLongLong(tuple_values[i]);
		core_ant(self)->position[i] = int_value;

	}

	return 0;

}

int ant_set_orientation(py_ant * self, PyObject * value, void * closure)
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

		LOG(puts(DEBUG("Error in getting unsigned long from orientation value.")));
		
		PyErr_SetString(PyExc_ValueError, "Invalid value for orientation. Value should be unsigned and less than or equal to 4294967295."); // ULONG_MAX aka " xstr(UINT_MAX) ".");
		return -1;

	}

	LOG(printf(DEBUG("Setting Ant position with unsigned long value of %ld...")"\n", long_value));

	core_ant(self)->orientation = long_value;


	return 0;

}

int ant_set_directive(py_ant * self, PyObject * value, void * closure)
{

	LOG(puts(TRACE("Setting ant directive...")));

	Py_INCREF(self);

	Py_DECREF(self->py_directive);
	if (value == NULL || value == Py_None)
	{

		LOG(puts(DEBUG("Resetting directive references...")));

		self->py_directive = (PyFunctionObject *)Py_None;
		Py_INCREF(Py_None);

	}
	else if (PyFunction_Check(value) || PyCFunction_Check(value))
	{

		// TODO PyMethod_New for implicit self reference
		// https://docs.python.org/3.7/c-api/method.html#method-objects
		Py_INCREF(value);
		self->py_directive = (PyFunctionObject *)value;

	}
	else
	{

		PyErr_SetString(PyExc_TypeError, "Expected a function value for Ant.directive");
		Py_DECREF(self);
		return -1;

	}

	Py_DECREF(self);

	LOG(puts(DEBUG("Successfully updated directive.")));

	return 0;

}


/* END SETTERS */

py_ant * ant_alloc(PyTypeObject * type, Py_ssize_t nitems)
{

	return (py_ant *)type->tp_alloc(type, nitems);

}

PyObject * ant_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

	// Initially, the position will be an empty tuple
	py_ant * self = ant_alloc(type, 0);
    if (self != NULL)
    {

		LOG(puts(DEBUG("Got a new Ant!")));

	}

    return (PyObject *) self; //TODO is NULL when None is passed to constructor

}

int ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	PyObject * arg = NULL;

	if (!PyArg_UnpackTuple(args, "Ant.__init__", 0, 1, &arg)) return -1;
	if (arg != NULL && !py_grid_check(arg))
	{

		PyErr_SetString(PyExc_TypeError, "Expected a Grid for single argument Ant constructor.");
		return -1;

	}

	self->ant.orientation = 0;
	self->ant.tuple_size = 0;
	self->ant.directive = (ant_directivefn) ant_t_directive_wrapper;
	self->py_directive = (PyFunctionObject *) Py_None;
	Py_INCREF(Py_None);
	
    return 0;

}

void ant_dealloc(py_ant * self)
{

    Py_TYPE(self)->tp_free((PyObject *) self);

}

static PyGetSetDef ant_getsetters[] = {

	{"position", (getter) ant_get_position, (setter) ant_set_position, "ant position", NULL},
	{"orientation", (getter) ant_get_orientation, (setter) ant_set_orientation, "ant orientation", NULL},  
	{"directive", (getter) ant_get_directive, (setter) ant_set_directive, "directive function called every pass by the grid", NULL}, 
	{NULL}

};

PyTypeObject py_ant_type = {
	
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "libant.Ant",
        .tp_doc = "An ant to move on the grid.",
        .tp_basicsize = sizeof(py_ant),
		.tp_itemsize = sizeof(INT),
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
		.tp_getset = ant_getsetters,
        .tp_new = ant_new,
        .tp_init = (initproc) ant_init,
        .tp_dealloc = (destructor) ant_dealloc,
		
};

