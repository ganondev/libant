#include <libant_grid_cartesian.h>
#include <quadtree/quadtree.h>

int grid_cartesian_init(py_grid * self, PyObject * args, PyObject * kwargs)
{

	ant_grid_t * grid = new_grid(); // QT is currently created by default but it should change.
	grid->tree->root = qt_node_create(0, 0, NULL);
	
    return 0;

}

static PyObject* grid_cartesian_insert(PyObject* self, PyObject* args)
{

	long long int x, y, value;

	if (PyArg_ParseTuple(args, "LLL:CartesianGrid.insert", &x, &y, &value))
	{

		grid_insert(((py_grid *)self)->grid, x, y, value);

		#ifdef LIBANT_DEBUG
		printf(TRACE("Insert of %lld to (%lld, %lld) successfull.\n"), x, y);
		#endif

	}
	else return NULL;

	Py_RETURN_NONE;

}

PyTypeObject py_grid_cartesian_type = {
	
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.CartesianGrid",
	.tp_doc = "Cartesian Grid backed by a quadtree.",
	.tp_basicsize = sizeof(py_grid),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_init = (initproc) grid_cartesian_init,
	
};
