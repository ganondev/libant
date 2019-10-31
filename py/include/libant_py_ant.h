#ifndef LIBANT_LIBANT_PY_ANT_H
#define LIBANT_LIBANT_PY_ANT_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include <libant.h>

#define py_ant_check(obj) PyObject_TypeCheck(obj, &py_ant_type)

typedef struct
{

	PyObject_HEAD
	ant_t * ant;
	PyObject * py_directive;

} py_ant;

PyObject * position_as_py_long(ant_t *, int); //todo inline

PyObject * langtons_ant_default_directive_wrapper(PyObject * module, PyObject * arg);

PyMethodDef langtons_ant_directive;

extern PyObject * langtons_ant_directive_func;

PyTupleObject * ant_get_position(py_ant *, void *);

PyLongObject * ant_get_orientation(py_ant *, void *);

PyObject * ant_get_directive(py_ant *, void *);

int ant_set_position(py_ant *, PyTupleObject *, void *);

int ant_set_orientation(py_ant *, PyObject *, void *);

int ant_set_directive(py_ant *, PyObject *, void *);

PyObject * ant_new(PyTypeObject *, PyObject *, PyObject *);

int ant_init(py_ant *, PyObject *, PyObject *);

void ant_dealloc(py_ant *);

#ifndef _WIN32
static
#endif
PyGetSetDef ant_getsetters[];

PyTypeObject py_ant_type;

PyObject * langtons_ant_default_directive_wrapper(PyObject * module, PyObject * arg);

PyMethodDef langtons_ant_directive;

#endif
