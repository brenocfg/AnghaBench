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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_TO_PID (void*) ; 
 scalar_t__ arg_kill_signal ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_request_stop(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        pid_t pid;

        assert(m);

        pid = PTR_TO_PID(userdata);

        if (arg_kill_signal > 0) {
                log_info("Container termination requested. Attempting to halt container.");
                (void) kill(pid, arg_kill_signal);
        } else {
                log_info("Container termination requested. Exiting.");
                sd_event_exit(sd_bus_get_event(sd_bus_message_get_bus(m)), 0);
        }

        return 0;
}