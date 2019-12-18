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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  manager_reset_all (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int match_prepare_for_sleep(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
        Manager *m = userdata;
        int b, r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "b", &b);
        if (r < 0) {
                log_debug_errno(r, "Failed to parse PrepareForSleep signal: %m");
                return 0;
        }

        if (b)
                return 0;

        log_debug("Coming back from suspend, resetting all connections...");

        (void) manager_reset_all(m);

        return 0;
}