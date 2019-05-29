#ifndef LIBANT_PY_MODULE_H
#define LIBANT_PY_MODULE_H

#include <Python.h>

#include "libant_py_ant.h"

static PyMethodDef module_methods[] = {
	
	{"langtons_ant_directive", (PyCFunction) langtons_ant_default_directive_wrapper, METH_O, "Default directive for langton's ant." },
	{NULL, NULL, 0, NULL}
	
};

static PyModuleDef libant = {
	
        PyModuleDef_HEAD_INIT,
        .m_name = "libant",
        .m_doc = "Example module that creates an extension type.",
        .m_size = -1,
		module_methods
		
};

PyMODINIT_FUNC PyInit_libant(void);

#endif