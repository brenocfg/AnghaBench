#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ FunctionObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyString_FromFormat (char*,char*) ; 

__attribute__((used)) static PyObject *
FunctionRepr(FunctionObject *self)
{
#ifdef Py_TRACE_REFS
    /* For unknown reason self->name may be NULL after calling
     * Finalize */
    return PyString_FromFormat("<vim.Function '%s'>",
	    (self->name == NULL ? "<NULL>" : (char *)self->name));
#else
    return PyString_FromFormat("<vim.Function '%s'>", (char *)self->name);
#endif
}