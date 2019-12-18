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
struct TYPE_4__ {scalar_t__ pending_reload_message; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 scalar_t__ sd_bus_message_unref (scalar_t__) ; 
 int sd_bus_send (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

int bus_send_pending_reload_message(Manager *m) {
        int r;

        assert(m);

        if (!m->pending_reload_message)
                return 0;

        /* If we cannot get rid of this message we won't dispatch any D-Bus messages, so that we won't end up wanting
         * to queue another message. */

        r = sd_bus_send(NULL, m->pending_reload_message, NULL);
        if (r < 0)
                log_warning_errno(r, "Failed to send queued message, ignoring: %m");

        m->pending_reload_message = sd_bus_message_unref(m->pending_reload_message);

        return 0;
}