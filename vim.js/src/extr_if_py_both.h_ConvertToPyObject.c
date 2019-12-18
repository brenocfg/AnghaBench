#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * v_string; int /*<<< orphan*/  v_dict; int /*<<< orphan*/  v_list; scalar_t__ v_float; scalar_t__ v_number; } ;
struct TYPE_5__ {int v_type; TYPE_1__ vval; } ;
typedef  TYPE_2__ typval_T ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * NEW_DICTIONARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NEW_FUNCTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEW_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/ * PyBytes_FromString (char*) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyFloat_FromDouble (double) ; 
 int /*<<< orphan*/ * PyLong_FromLong (long) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
#define  VAR_DICT 134 
#define  VAR_FLOAT 133 
#define  VAR_FUNC 132 
#define  VAR_LIST 131 
#define  VAR_NUMBER 130 
#define  VAR_STRING 129 
#define  VAR_UNKNOWN 128 

__attribute__((used)) static PyObject *
ConvertToPyObject(typval_T *tv)
{
    if (tv == NULL)
    {
	PyErr_SET_VIM(N_("internal error: NULL reference passed"));
	return NULL;
    }
    switch (tv->v_type)
    {
	case VAR_STRING:
	    return PyBytes_FromString(tv->vval.v_string == NULL
					    ? "" : (char *)tv->vval.v_string);
	case VAR_NUMBER:
	    return PyLong_FromLong((long) tv->vval.v_number);
#ifdef FEAT_FLOAT
	case VAR_FLOAT:
	    return PyFloat_FromDouble((double) tv->vval.v_float);
#endif
	case VAR_LIST:
	    return NEW_LIST(tv->vval.v_list);
	case VAR_DICT:
	    return NEW_DICTIONARY(tv->vval.v_dict);
	case VAR_FUNC:
	    return NEW_FUNCTION(tv->vval.v_string == NULL
					  ? (char_u *)"" : tv->vval.v_string);
	case VAR_UNKNOWN:
	    Py_INCREF(Py_None);
	    return Py_None;
	default:
	    PyErr_SET_VIM(N_("internal error: invalid value type"));
	    return NULL;
    }
}