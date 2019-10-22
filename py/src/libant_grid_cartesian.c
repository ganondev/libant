#include <libant_grid_cartesian.h>

int grid_cartesian_init(py_grid * self, PyObject * args, PyObject * kwargs)
{

	self->grid = new_grid();
	
    return 0;

}

PyTypeObject py_grid_cartesian_type = {
	
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.CartesianGrid",
	.tp_doc = "Cartesian Grid backed by a quadtree.",
	.tp_basicsize = sizeof(py_grid),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_init = (initproc) grid_cartesian_init,
	
};
