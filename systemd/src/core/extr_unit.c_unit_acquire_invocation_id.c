#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_unit_error_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_id128_randomize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (int /*<<< orphan*/ *) ; 
 int unit_set_invocation_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int unit_acquire_invocation_id(Unit *u) {
        sd_id128_t id;
        int r;

        assert(u);

        r = sd_id128_randomize(&id);
        if (r < 0)
                return log_unit_error_errno(u, r, "Failed to generate invocation ID for unit: %m");

        r = unit_set_invocation_id(u, id);
        if (r < 0)
                return log_unit_error_errno(u, r, "Failed to set invocation ID for unit: %m");

        unit_add_to_dbus_queue(u);
        return 0;
}