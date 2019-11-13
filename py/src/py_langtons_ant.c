#include <stdio.h>
#include <py_langtons_ant.h>
#include <libant_grid.h>
#include <libant_grid_cartesian.h>

PyObject* langtons_ant_default_directive_wrapper(PyObject* module, PyObject* args)
{

	PyObject* arg_ant, * grid;

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

		py_ant* ant = (py_ant*)arg_ant;

		Py_INCREF(ant);
		Py_INCREF(grid);

		if (core_ant(ant)->orientation < 0 || core_ant(ant)->orientation > 3)
		{

			PyErr_SetString(PyExc_IndexError, "Langton's ant has only four valid orientations. Orientation field should be valued between 0 and 3.");
			Py_DECREF(ant);
			Py_DECREF(grid);
			return NULL;

		}

		langtons_ant_default_directive(core_ant(ant), core_grid(grid));

		Py_DECREF(ant);
		Py_DECREF(grid);

		Py_RETURN_NONE;

	}

	LOG(puts(ERROR("Argument parsing failed.")));

	if (!PyErr_Occurred()) PyErr_SetString(PyExc_Exception, "Arguments could not be parsed."); //TODO this needs to be specified

	return NULL;

}

PyMethodDef langtons_ant_directive = { "langtons_ant_directive", (PyCFunction)langtons_ant_default_directive_wrapper, METH_VARARGS, "Default directive for langton's ant." };

PyFunctionObject* langtons_ant_directive_func = NULL;

int langtons_ant_init(py_ant * self, PyObject * args, PyObject * kwargs)
{

	PyObject * arg = NULL;

	if (!PyArg_UnpackTuple(args, "LangtonsAnt.__init__", 0, 1, &arg)) return -1; // TODO can probably just call libant_py_ant::ant_init
	if (arg != NULL && !py_grid_check(arg))
	{

		PyErr_SetString(PyExc_TypeError, "Expected a Grid for single argument Ant constructor.");
		return -1;

	}

	self->py_directive = langtons_ant_directive_func;
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
