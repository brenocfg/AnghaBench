#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ ListObject ;

/* Variables and functions */
 int /*<<< orphan*/  DESTRUCTOR_FINISH (TYPE_1__*) ; 
 int /*<<< orphan*/  lastlist ; 
 int /*<<< orphan*/  list_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyll_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ListDestructor(ListObject *self)
{
    pyll_remove(&self->ref, &lastlist);
    list_unref(self->list);

    DESTRUCTOR_FINISH(self);
}