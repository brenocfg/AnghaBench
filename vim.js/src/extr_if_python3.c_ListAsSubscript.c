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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  ListObject ;

/* Variables and functions */
 int ListAssItem (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int ListAssSlice (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListLength (int /*<<< orphan*/ *) ; 
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_GetIndicesEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  RAISE_INVALID_INDEX_TYPE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Py_ssize_t
ListAsSubscript(PyObject *self, PyObject *idx, PyObject *obj)
{
    if (PyLong_Check(idx))
    {
	long _idx = PyLong_AsLong(idx);
	return ListAssItem((ListObject *)(self), _idx, obj);
    }
    else if (PySlice_Check(idx))
    {
	Py_ssize_t start, stop, step, slicelen;

	if (PySlice_GetIndicesEx(idx, ListLength((ListObject *)(self)),
				 &start, &stop, &step, &slicelen) < 0)
	    return -1;
	return ListAssSlice((ListObject *)(self), start, stop, obj);
    }
    else
    {
	RAISE_INVALID_INDEX_TYPE(idx);
	return -1;
    }
}