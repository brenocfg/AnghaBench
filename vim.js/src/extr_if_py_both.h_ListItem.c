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
struct TYPE_6__ {int /*<<< orphan*/  li_tv; } ;
typedef  TYPE_1__ listitem_T ;
struct TYPE_7__ {int /*<<< orphan*/  list; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ ListObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ConvertToPyObject (int /*<<< orphan*/ *) ; 
 scalar_t__ ListLength (TYPE_2__*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_VIM_FORMAT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 TYPE_1__* list_find (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static PyObject *
ListItem(ListObject *self, Py_ssize_t index)
{
    listitem_T	*li;

    if (index >= ListLength(self))
    {
	PyErr_SET_STRING(PyExc_IndexError, N_("list index out of range"));
	return NULL;
    }
    li = list_find(self->list, (long) index);
    if (li == NULL)
    {
	/* No more suitable format specifications in python-2.3 */
	PyErr_VIM_FORMAT(N_("internal error: failed to get vim list item %d"),
		(int) index);
	return NULL;
    }
    return ConvertToPyObject(&li->li_tv);
}