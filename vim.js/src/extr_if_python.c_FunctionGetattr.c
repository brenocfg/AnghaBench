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
struct TYPE_2__ {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ FunctionObject ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionAttrs ; 
 int /*<<< orphan*/  FunctionMethods ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
FunctionGetattr(PyObject *self, char *name)
{
    FunctionObject	*this = (FunctionObject *)(self);

    if (strcmp(name, "name") == 0)
	return PyString_FromString((char *)(this->name));
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, FunctionAttrs);
    else
	return Py_FindMethod(FunctionMethods, self, name);
}