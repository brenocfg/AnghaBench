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
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_1__ RangeObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_BuildValue (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_ssize_t_fmt ; 
 int /*<<< orphan*/  RangeAttrs ; 
 int /*<<< orphan*/  RangeMethods ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
RangeGetattr(PyObject *self, char *name)
{
    if (strcmp(name, "start") == 0)
	return Py_BuildValue(Py_ssize_t_fmt, ((RangeObject *)(self))->start - 1);
    else if (strcmp(name, "end") == 0)
	return Py_BuildValue(Py_ssize_t_fmt, ((RangeObject *)(self))->end - 1);
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, RangeAttrs);
    else
	return Py_FindMethod(RangeMethods, self, name);
}