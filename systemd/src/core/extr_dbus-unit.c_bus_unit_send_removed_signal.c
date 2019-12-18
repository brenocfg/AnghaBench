#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; int /*<<< orphan*/  bus_track; int /*<<< orphan*/  manager; scalar_t__ in_dbus_queue; int /*<<< orphan*/  sent_dbus_new_signal; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_foreach_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bus_unit_send_change_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_removed_signal ; 

void bus_unit_send_removed_signal(Unit *u) {
        int r;
        assert(u);

        if (!u->sent_dbus_new_signal || u->in_dbus_queue)
                bus_unit_send_change_signal(u);

        if (!u->id)
                return;

        r = bus_foreach_bus(u->manager, u->bus_track, send_removed_signal, u);
        if (r < 0)
                log_unit_debug_errno(u, r, "Failed to send unit remove signal for %s: %m", u->id);
}