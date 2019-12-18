#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ RangeObject ;
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PySlice_GetIndicesEx (int /*<<< orphan*/ *,scalar_t__,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  RAISE_INVALID_INDEX_TYPE (int /*<<< orphan*/ *) ; 
 int RangeAsItem (int /*<<< orphan*/ *,long,int /*<<< orphan*/ *) ; 
 int RangeAsSlice (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Py_ssize_t
RangeAsSubscript(PyObject *self, PyObject *idx, PyObject *val)
{
    if (PyLong_Check(idx))
    {
	long n = PyLong_AsLong(idx);
	return RangeAsItem(self, n, val);
    } else if (PySlice_Check(idx))
    {
	Py_ssize_t start, stop, step, slicelen;

	if (PySlice_GetIndicesEx((PyObject *)idx,
		((RangeObject *)(self))->end-((RangeObject *)(self))->start+1,
		&start, &stop,
		&step, &slicelen) < 0)
	{
	    return -1;
	}
	return RangeAsSlice(self, start, stop, val);
    }
    else
    {
	RAISE_INVALID_INDEX_TYPE(idx);
	return -1;
    }
}