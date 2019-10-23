#include <libant_grid_cartesian.h>
#include <quadtree/quadtree.h>

static PyObject * grid_cartesian_get(PyObject * self, PyObject * args)
{

	#ifdef LIBANT_DEBUG
	puts(TRACE("Beginning retreival of grid value..."));
	#endif

	PyObject * x_or_coord_tuple;
	PyObject * y = NULL;

	if (PyArg_UnpackTuple(args, "CartesianGrid.get", 1, 2, &x_or_coord_tuple, &y))
	{

		if (y == NULL)
		{

			// Other arg should be a tuple. Proceed with that assumption
			if (!PyTuple_Check(x_or_coord_tuple) || (PyTuple_Size(x_or_coord_tuple) != 2))
			{

				PyErr_SetString(PyExc_TypeError, "Single argument should be a 2-tuple.");
				return NULL;

			}

			y = PyTuple_GetItem(x_or_coord_tuple, 1);
			x_or_coord_tuple = PyTuple_GetItem(x_or_coord_tuple, 0);

		}
		
		// In any case, both variables should be PyObject * by now
		if (!PyLong_Check(x_or_coord_tuple) || !PyLong_Check(y))
		{

			PyErr_SetString(PyExc_TypeError, "Coordinate components should be integers.");
			return NULL;

		}

		INT x_coord = PyLong_AsLongLong(x_or_coord_tuple);
		INT y_coord = PyLong_AsLongLong(y);

		if ((x_coord == -1 || y_coord == -1) && PyErr_Occurred()) return NULL;

		INT value = grid_get(((py_grid *) self)->grid, x_coord, y_coord);
		#ifdef LIBANT_DEBUG
		printf(DEBUG("Found integer value: %lld\n"), value);
		#endif

		PyObject * py_long_value = PyLong_FromLongLong(value);
		Py_INCREF(py_long_value);
		return py_long_value;

	}

	#ifdef LIBANT_DEBUG
	puts(ERROR("Argument parsing failed."));
	#endif

	if (!PyErr_Occurred()) PyErr_SetString(PyExc_Exception, "Arguments could not be parsed."); //TODO this needs to be specified

	return NULL;

}

static PyObject* grid_cartesian_insert(PyObject* self, PyObject* args)
{

	long long int x, y, value;

	if (PyArg_ParseTuple(args, "LLL:CartesianGrid.insert", &x, &y, &value))
	{

		grid_insert(((py_grid *)self)->grid, x, y, value);

		#ifdef LIBANT_DEBUG
		printf(TRACE("Insert of %lld to (%lld, %lld) successfull.\n"), value, x, y);
		#endif

	}
	else return NULL;

	Py_RETURN_NONE;

}

int grid_cartesian_init(py_grid * self, PyObject * args, PyObject * kwargs)
{

	ant_grid_t * grid = new_grid(); // QT is currently created by default but it should change.
	self->grid = grid;
    return 0;

}

static PyMethodDef grid_cartesian_methods[] = {

	{"get", (PyCFunction) grid_cartesian_get, METH_VARARGS, "Retreive the integer value stored in the cell at the given location. Accepts a single 2-tuple of ints or 2 ints."},
	{"insert", (PyCFunction) grid_cartesian_insert, METH_VARARGS, "Inserts the given integer into the specified location." },
	{NULL}

};

PyTypeObject py_grid_cartesian_type = {
	
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.CartesianGrid",
	.tp_doc = "Cartesian Grid backed by a quadtree.",
	.tp_basicsize = sizeof(py_grid),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_methods = grid_cartesian_methods,
	.tp_init = (initproc) grid_cartesian_init,
	
};
