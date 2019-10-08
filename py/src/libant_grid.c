#include <libant_grid.h>
#include <Python.h>

#include <antmacro.h>

PyObject * grid_new(PyTypeObject * type, PyObject * args, PyObject * kwargs)
{

	py_grid * self = (py_grid *) type->tp_alloc(type, 0);
	if (self != NULL)
	{

		puts(DEBUG("Got a new Grid!"));

	}

	return (PyObject *) self;

}

int grid_init(py_grid * self, PyObject * args, PyObject * kwargs)
{

	self->grid = new_grid();
	Py_INCREF(Py_None);

}

void grid_dealloc(py_grid * self)
{

	Py_TYPE(self)->tp_free((PyObject *) self);

}

PyGetSetDef grid_getsetters[] = {

	{NULL}

};

PyTypeObject py_grid_type = {

	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.Grid",
	.tp_doc = "A grid to represent the world in which automata simulations occur.",
	.tp_basicsize = sizeof(py_grid),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_getset = grid_getsetters,
	.tp_new = grid_new,
	.tp_init = (initproc) grid_init,
	.tp_dealloc = (destructor) grid_dealloc,

};
