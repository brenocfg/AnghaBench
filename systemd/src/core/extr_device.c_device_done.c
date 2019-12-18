#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {int /*<<< orphan*/  wants_property; } ;
typedef  TYPE_1__ Device ;

/* Variables and functions */
 TYPE_1__* DEVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unset_sysfs (TYPE_1__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_done(Unit *u) {
        Device *d = DEVICE(u);

        assert(d);

        device_unset_sysfs(d);
        d->wants_property = strv_free(d->wants_property);
}