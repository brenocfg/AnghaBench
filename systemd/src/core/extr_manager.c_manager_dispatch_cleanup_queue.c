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
struct TYPE_6__ {TYPE_2__* in_cleanup_queue; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_7__ {TYPE_1__* cleanup_queue; } ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  unit_free (TYPE_1__*) ; 

__attribute__((used)) static unsigned manager_dispatch_cleanup_queue(Manager *m) {
        Unit *u;
        unsigned n = 0;

        assert(m);

        while ((u = m->cleanup_queue)) {
                assert(u->in_cleanup_queue);

                unit_free(u);
                n++;
        }

        return n;
}