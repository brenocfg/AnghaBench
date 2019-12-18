#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  v_type; scalar_t__ v_lock; } ;
struct TYPE_6__ {TYPE_5__ li_tv; } ;
typedef  TYPE_1__ listitem_T ;
typedef  int /*<<< orphan*/  list_T ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyIter_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VAR_UNKNOWN ; 
 int _ConvertFromPyObject (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* listitem_alloc () ; 
 int /*<<< orphan*/  listitem_free (TYPE_1__*) ; 

__attribute__((used)) static int
list_py_concat(list_T *l, PyObject *obj, PyObject *lookup_dict)
{
    PyObject	*iterator;
    PyObject	*item;
    listitem_T	*li;

    if (!(iterator = PyObject_GetIter(obj)))
	return -1;

    while ((item = PyIter_Next(iterator)))
    {
	if (!(li = listitem_alloc()))
	{
	    PyErr_NoMemory();
	    Py_DECREF(item);
	    Py_DECREF(iterator);
	    return -1;
	}
	li->li_tv.v_lock = 0;
	li->li_tv.v_type = VAR_UNKNOWN;

	if (_ConvertFromPyObject(item, &li->li_tv, lookup_dict) == -1)
	{
	    Py_DECREF(item);
	    Py_DECREF(iterator);
	    listitem_free(li);
	    return -1;
	}

	Py_DECREF(item);

	list_append(l, li);
    }

    Py_DECREF(iterator);

    /* Iterator may have finished due to an exception */
    if (PyErr_Occurred())
	return -1;

    return 0;
}