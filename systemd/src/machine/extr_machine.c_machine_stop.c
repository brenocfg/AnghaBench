#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int stopping; int /*<<< orphan*/  manager; int /*<<< orphan*/  class; } ;
typedef  TYPE_1__ Machine ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHINE_CONTAINER ; 
 int /*<<< orphan*/  MACHINE_VM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  machine_save (TYPE_1__*) ; 
 int machine_stop_scope (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_enqueue_nscd_cache_flush (int /*<<< orphan*/ ) ; 

int machine_stop(Machine *m) {
        int r;
        assert(m);

        if (!IN_SET(m->class, MACHINE_CONTAINER, MACHINE_VM))
                return -EOPNOTSUPP;

        r = machine_stop_scope(m);

        m->stopping = true;

        machine_save(m);
        (void) manager_enqueue_nscd_cache_flush(m->manager);

        return r;
}