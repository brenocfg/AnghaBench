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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_foreach_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  send_reloading ; 

void bus_manager_send_reloading(Manager *m, bool active) {
        int r;

        assert(m);

        r = bus_foreach_bus(m, NULL, send_reloading, INT_TO_PTR(active));
        if (r < 0)
                log_debug_errno(r, "Failed to send reloading signal: %m");
}