#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ unit; TYPE_1__* manager; } ;
struct TYPE_5__ {int /*<<< orphan*/  machine_units; } ;
typedef  TYPE_2__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mfree (scalar_t__) ; 

void machine_release_unit(Machine *m) {
        assert(m);

        if (!m->unit)
                return;

        (void) hashmap_remove(m->manager->machine_units, m->unit);
        m->unit = mfree(m->unit);
}