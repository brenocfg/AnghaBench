#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 long INT_MAX ; 
 long INT_MIN ; 
 int NUMBER_INT ; 
 int NUMBER_NATURAL ; 
 int NUMBER_UNSIGNED ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OverflowError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 long PyInt_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyNumber_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyNumber_Long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_TYPE_NAME (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
NumberToLong(PyObject *obj, long *result, int flags)
{
#if PY_MAJOR_VERSION < 3
    if (PyInt_Check(obj))
    {
	*result = PyInt_AsLong(obj);
	if (PyErr_Occurred())
	    return -1;
    }
    else
#endif
    if (PyLong_Check(obj))
    {
	*result = PyLong_AsLong(obj);
	if (PyErr_Occurred())
	    return -1;
    }
    else if (PyNumber_Check(obj))
    {
	PyObject	*num;

	if (!(num = PyNumber_Long(obj)))
	    return -1;

	*result = PyLong_AsLong(num);

	Py_DECREF(num);

	if (PyErr_Occurred())
	    return -1;
    }
    else
    {
#if PY_MAJOR_VERSION < 3
	PyErr_FORMAT(PyExc_TypeError,
		N_("expected int(), long() or something supporting "
		   "coercing to long(), but got %s"),
		Py_TYPE_NAME(obj));
#else
	PyErr_FORMAT(PyExc_TypeError,
		N_("expected int() or something supporting coercing to int(), "
		   "but got %s"),
		Py_TYPE_NAME(obj));
#endif
	return -1;
    }

    if (flags & NUMBER_INT)
    {
	if (*result > INT_MAX)
	{
	    PyErr_SET_STRING(PyExc_OverflowError,
		    N_("value is too large to fit into C int type"));
	    return -1;
	}
	else if (*result < INT_MIN)
	{
	    PyErr_SET_STRING(PyExc_OverflowError,
		    N_("value is too small to fit into C int type"));
	    return -1;
	}
    }

    if (flags & NUMBER_NATURAL)
    {
	if (*result <= 0)
	{
	    PyErr_SET_STRING(PyExc_ValueError,
		    N_("number must be greater then zero"));
	    return -1;
	}
    }
    else if (flags & NUMBER_UNSIGNED)
    {
	if (*result < 0)
	{
	    PyErr_SET_STRING(PyExc_ValueError,
		    N_("number must be greater or equal to zero"));
	    return -1;
	}
    }

    return 0;
}