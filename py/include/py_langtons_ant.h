#ifndef PY_LANGTONS_ANT_H
#define PY_LANGTONS_ANT_H

#include <stdbool.h>
#include <limits.h>

#include <Python.h>
#include <structmember.h>

#include "libant_py_ant.h"

int langtons_ant_init(py_ant *, PyObject *, PyObject *);

PyTypeObject py_langtons_ant_type;

#endif
