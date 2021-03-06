#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lv_refcount; } ;
typedef  TYPE_1__ list_T ;
struct TYPE_9__ {int /*<<< orphan*/  ref; TYPE_1__* list; } ;
struct TYPE_8__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ ListObject ;

/* Variables and functions */
 int /*<<< orphan*/  lastlist ; 
 int /*<<< orphan*/  pyll_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
ListNew(PyTypeObject *subtype, list_T *list)
{
    ListObject	*self;

    self = (ListObject *) subtype->tp_alloc(subtype, 0);
    if (self == NULL)
	return NULL;
    self->list = list;
    ++list->lv_refcount;

    pyll_add((PyObject *)(self), &self->ref, &lastlist);

    return (PyObject *)(self);
}