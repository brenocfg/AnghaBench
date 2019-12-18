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

/* Variables and functions */
 scalar_t__ arg_send_sighup ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_create_error (int) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,scalar_t__) ; 

__attribute__((used)) static int transient_kill_set_properties(sd_bus_message *m) {
        int r;

        assert(m);

        if (arg_send_sighup) {
                r = sd_bus_message_append(m, "(sv)", "SendSIGHUP", "b", arg_send_sighup);
                if (r < 0)
                        return bus_log_create_error(r);
        }

        return 0;
}