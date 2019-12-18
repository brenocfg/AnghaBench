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
typedef  int /*<<< orphan*/ * sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  PTYForward ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int pty_forward_set_ignore_vhangup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_machine_removed(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        PTYForward ** forward = (PTYForward**) userdata;
        int r;

        assert(m);
        assert(forward);

        if (*forward) {
                /* If the forwarder is already initialized, tell it to
                 * exit on the next vhangup(), so that we still flush
                 * out what might be queued and exit then. */

                r = pty_forward_set_ignore_vhangup(*forward, false);
                if (r >= 0)
                        return 0;

                log_error_errno(r, "Failed to set ignore_vhangup flag: %m");
        }

        /* On error, or when the forwarder is not initialized yet, quit immediately */
        sd_event_exit(sd_bus_get_event(sd_bus_message_get_bus(m)), EXIT_FAILURE);
        return 0;
}