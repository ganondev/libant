#ifndef LIBANT_LIBANT_PY_DEF_H
#define LIBANT_LIBANT_PY_DEF_H

#ifdef PY_DEBUG
#define ANSI_RED "\033[31;1;4m"
#define ANSI_END "\033[0m"
#define DEBUG(tok) ANSI_RED tok ANSI_END
#endif

#define str(x) #x
#define xstr(x) str(x)

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include "anttype.h"

typedef struct
{

	PyObject_HEAD
	ant_t * ant;

} py_ant;

//static PyMemberDef ant_members[] = {
//
//        {"test", T_INT, offsetof(py_ant, test), 0, "test field"},
//        {NULL}
//
//};

static PyTupleObject * ant_get_position(py_ant *, void *);

static PyLongObject * ant_get_orientation(py_ant *, void*);

static int ant_set_position(py_ant *, PyTupleObject *, void *);

static int ant_set_orientation(py_ant *, PyObject *, void *);

static PyGetSetDef ant_getsetters[] = {

	{"position", (getter) ant_get_position, (setter) ant_set_position, "ant position", NULL},
	{"orientation", (getter) ant_get_orientation, (setter) ant_set_orientation, "ant orientation", NULL},  
	//{"directive", (getter) NULL, (setter) NULL, "directive function called every pass by the grid", NULL}, 
	{NULL}

};

static PyObject * ant_new(PyTypeObject *, PyObject *, PyObject *);

static int ant_init(py_ant *, PyObject *, PyObject *);

static void ant_dealloc(py_ant *);

static PyTypeObject py_ant_type = {
        PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "libant.Ant",
        .tp_doc = "An ant to move on the grid.",
        .tp_basicsize = sizeof(py_ant),
        .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
        //.tp_members = ant_members,
		.tp_getset = ant_getsetters,
        .tp_new = ant_new,
        .tp_init = (initproc) ant_init,
        .tp_dealloc = (destructor) ant_dealloc,
};

static PyModuleDef libant = {
        PyModuleDef_HEAD_INIT,
        .m_name = "libant",
        .m_doc = "Example module that creates an extension type.",
        .m_size = -1,
};

PyMODINIT_FUNC PyInit_libant(void);

#endif //LIBANT_LIBANT_PY_DEF_H
