#include <stdio.h>
#include "py_langtons_ant.h"
#include "antmacro.h"

int langtons_ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	ant_init(self, args, kwargs);
	self->ant->directive = langtons_ant_default_directive;
	self->py_directive = langtons_ant_directive_func;
	
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
