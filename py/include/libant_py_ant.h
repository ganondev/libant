#ifndef LIBANT_LIBANT_PY_ANT_H
#define LIBANT_LIBANT_PY_ANT_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include <libant.h>

#define py_ant_check(obj) PyObject_TypeCheck(obj, &py_ant_type)

#define core_ant(obj) ((ant_t *)&(((py_ant *)obj)->ant))

typedef struct
{

	PyObject_HEAD
	PyFunctionObject * py_directive; //TODO PyMethodObject
	ant_t ant;

} py_ant;

inline PyObject * position_as_py_long(ant_t * ant, int index)
{
	
	return PyLong_FromLongLong(ant->position[index]);
	
}

void ant_t_directive_wrapper(ant_t *, ant_grid_t *);

PyObject * langtons_ant_default_directive_wrapper(PyObject * module, PyObject * arg);

PyMethodDef langtons_ant_directive;

extern PyFunctionObject * langtons_ant_directive_func;

PyTupleObject * ant_get_position(py_ant *, void *);

int ant_set_position(py_ant *, PyTupleObject *, void *);

py_ant * ant_alloc(PyTypeObject *, Py_ssize_t);

int ant_init(py_ant *, PyObject *, PyObject *);

PyTypeObject py_ant_type;

#endif
