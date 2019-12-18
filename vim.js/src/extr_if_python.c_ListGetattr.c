#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* list; } ;
struct TYPE_3__ {int /*<<< orphan*/  lv_lock; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ ListObject ;

/* Variables and functions */
 int /*<<< orphan*/  ListAttrs ; 
 int /*<<< orphan*/  ListMethods ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
ListGetattr(PyObject *self, char *name)
{
    if (strcmp(name, "locked") == 0)
	return PyInt_FromLong(((ListObject *)(self))->list->lv_lock);
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, ListAttrs);

    return Py_FindMethod(ListMethods, self, name);
}