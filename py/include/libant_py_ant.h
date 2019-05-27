#ifndef LIBANT_LIBANT_PY_ANT_H
#define LIBANT_LIBANT_PY_ANT_H

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
#include "antalgo.h"

typedef struct
{

	PyObject_HEAD
	ant_t * ant;

} py_ant;

PyTupleObject * ant_get_position(py_ant *, void *);

PyLongObject * ant_get_orientation(py_ant *, void*);

int ant_set_position(py_ant *, PyTupleObject *, void *);

int ant_set_orientation(py_ant *, PyObject *, void *);

PyObject * ant_new(PyTypeObject *, PyObject *, PyObject *);

int ant_init(py_ant *, PyObject *, PyObject *);

void ant_dealloc(py_ant *);

static PyGetSetDef ant_getsetters[];

PyTypeObject py_ant_type;

#endif
