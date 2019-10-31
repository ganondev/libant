#include <stdio.h>
#include <py_langtons_ant.h>
#include <libant_grid.h>
#include <libant_grid_cartesian.h>

int langtons_ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	PyObject * arg = NULL;

	if (!PyArg_UnpackTuple(args, "LangtonsAnt.__init__", 0, 1, &arg)) return -1; // TODO can probably just call libant_py_ant::ant_init
	if (arg != NULL && !py_grid_check(arg))
	{

		PyErr_SetString(PyExc_TypeError, "Expected a Grid for single argument Ant constructor.");
		return -1;

	}

	self->ant = create_langtons_ant();
	self->py_directive = (PyObject *)langtons_ant_directive_func;
	Py_INCREF(Py_None);

	return 0;

}

PyTypeObject py_langtons_ant_type = {
	
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "libant.LangtonsAnt",
	.tp_doc = "Pre-Configured Langtons Ant",
	.tp_basicsize = sizeof(py_ant),
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_init = (initproc) langtons_ant_init,
	
};
