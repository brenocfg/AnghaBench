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

/* Variables and functions */
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_path (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_message_is_method_call (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ sd_bus_message_is_method_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int object_callback(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        int r;

        if (sd_bus_message_is_method_error(m, NULL))
                return 0;

        if (sd_bus_message_is_method_call(m, "org.object.test", "Foobar")) {
                log_info("Invoked Foobar() on %s", sd_bus_message_get_path(m));

                r = sd_bus_reply_method_return(m, NULL);
                if (r < 0)
                        return log_error_errno(r, "Failed to send reply: %m");

                return 1;
        }

        return 0;
}