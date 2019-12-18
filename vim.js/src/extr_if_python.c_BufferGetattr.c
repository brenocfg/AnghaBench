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
typedef  int /*<<< orphan*/  BufferObject ;

/* Variables and functions */
 int /*<<< orphan*/ * BufferAttr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * BufferAttrValid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BufferMethods ; 
 scalar_t__ CheckBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static PyObject *
BufferGetattr(PyObject *self, char *name)
{
    PyObject *r;

    if ((r = BufferAttrValid((BufferObject *)(self), name)))
	return r;

    if (CheckBuffer((BufferObject *)(self)))
	return NULL;

    r = BufferAttr((BufferObject *)(self), name);
    if (r || PyErr_Occurred())
	return r;
    else
	return Py_FindMethod(BufferMethods, self, name);
}