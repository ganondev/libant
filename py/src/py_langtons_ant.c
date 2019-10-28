#include <stdio.h>
#include <py_langtons_ant.h>
#include <libant_grid.h>
#include <libant_grid_cartesian.h>

int langtons_ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	PyObject * arg;

	if (!PyArg_UnpackTuple(args, "Ant.__init__", 1, 1, &arg) || !py_grid_cartesian_check(arg)) return -1;

	self->ant = create_langtons_ant(((py_grid *)self)->grid);
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
