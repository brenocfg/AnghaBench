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
typedef  int /*<<< orphan*/  TabPageObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ CheckTabPage (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TabPageAttr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TabPageAttrValid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TabPageMethods ; 

__attribute__((used)) static PyObject *
TabPageGetattr(PyObject *self, char *name)
{
    PyObject *r;

    if ((r = TabPageAttrValid((TabPageObject *)(self), name)))
	return r;

    if (CheckTabPage((TabPageObject *)(self)))
	return NULL;

    r = TabPageAttr((TabPageObject *)(self), name);
    if (r || PyErr_Occurred())
	return r;
    else
	return Py_FindMethod(TabPageMethods, self, name);
}