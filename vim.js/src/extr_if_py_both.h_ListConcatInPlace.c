#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lv_lock; } ;
typedef  TYPE_1__ list_T ;
struct TYPE_7__ {TYPE_1__* list; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ ListObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 
 int /*<<< orphan*/  RAISE_LOCKED_LIST ; 
 int list_py_concat (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ListConcatInPlace(ListObject *self, PyObject *obj)
{
    list_T	*l = self->list;
    PyObject	*lookup_dict;

    if (l->lv_lock)
    {
	RAISE_LOCKED_LIST;
	return NULL;
    }

    if (!(lookup_dict = PyDict_New()))
	return NULL;

    if (list_py_concat(l, obj, lookup_dict) == -1)
    {
	Py_DECREF(lookup_dict);
	return NULL;
    }
    Py_DECREF(lookup_dict);

    Py_INCREF(self);
    return (PyObject *)(self);
}