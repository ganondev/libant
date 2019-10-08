#ifndef LIBANT_PY_MODULE_H
#define LIBANT_PY_MODULE_H

#include <Python.h>

#include <libant_py_ant.h>

PyMethodDef module_methods[] = {

	{NULL, NULL, 0, NULL}
	
};

PyModuleDef libant = {
	
        PyModuleDef_HEAD_INIT,
        .m_name = "libant",
        .m_doc = "Example module that creates an extension type.",
        .m_size = -1,
		module_methods
		
};

PyMODINIT_FUNC PyInit_libant(void);

#endif
