#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  win_T ;
struct TYPE_4__ {TYPE_2__* tabObject; } ;
typedef  TYPE_1__ WinListObject ;
struct TYPE_5__ {int /*<<< orphan*/  tab; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  scalar_t__ PyInt ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/ * W_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WindowNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curtab ; 
 int /*<<< orphan*/ * get_firstwin (TYPE_2__*) ; 

__attribute__((used)) static PyObject *
WinListItem(WinListObject *self, PyInt n)
{
    win_T *w;

    if (!(w = get_firstwin(self->tabObject)))
	return NULL;

    for (; w != NULL; w = W_NEXT(w), --n)
	if (n == 0)
	    return WindowNew(w, self->tabObject? self->tabObject->tab: curtab);

    PyErr_SET_STRING(PyExc_IndexError, N_("no such window"));
    return NULL;
}