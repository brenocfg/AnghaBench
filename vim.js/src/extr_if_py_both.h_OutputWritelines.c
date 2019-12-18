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
typedef  int /*<<< orphan*/  OutputObject ;

/* Variables and functions */
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyIter_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ write_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
OutputWritelines(OutputObject *self, PyObject *seq)
{
    PyObject	*iterator;
    PyObject	*item;

    if (!(iterator = PyObject_GetIter(seq)))
	return NULL;

    while ((item = PyIter_Next(iterator)))
    {
	if (write_output(self, item))
	{
	    Py_DECREF(iterator);
	    Py_DECREF(item);
	    return NULL;
	}
	Py_DECREF(item);
    }

    Py_DECREF(iterator);

    /* Iterator may have finished due to an exception */
    if (PyErr_Occurred())
	return NULL;

    Py_INCREF(Py_None);
    return Py_None;
}