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
struct TYPE_4__ {int /*<<< orphan*/  manager; int /*<<< orphan*/  sent_dbus_new_signal; int /*<<< orphan*/  in_dbus_queue; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_unit_send_change_signal (TYPE_1__*) ; 

void bus_unit_send_pending_change_signal(Unit *u, bool including_new) {

        /* Sends out any pending change signals, but only if they really are pending. This call is used when we are
         * about to change state in order to force out a PropertiesChanged signal beforehand if there was one pending
         * so that clients can follow the full state transition */

        if (!u->in_dbus_queue) /* If not enqueued, don't bother */
                return;

        if (!u->sent_dbus_new_signal && !including_new) /* If the unit was never announced, don't bother, it's fine if
                                                         * the unit appears in the new state right-away (except if the
                                                         * caller explicitly asked us to send it anyway) */
                return;

        if (MANAGER_IS_RELOADING(u->manager)) /* Don't generate unnecessary PropertiesChanged signals for the same unit
                                               * when we are reloading. */
                return;

        bus_unit_send_change_signal(u);
}