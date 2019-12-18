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
typedef  int /*<<< orphan*/  WaitForItem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 
 int wait_for_item_parse_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_properties_changed(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        WaitForItem *item = userdata;
        const char *interface;
        int r;

        assert(item);

        r = sd_bus_message_read(m, "s", &interface);
        if (r < 0) {
                log_debug_errno(r, "Failed to parse PropertiesChanged signal: %m");
                return 0;
        }

        if (!streq(interface, "org.freedesktop.systemd1.Unit"))
                return 0;

        r = wait_for_item_parse_properties(item, m);
        if (r < 0)
                log_debug_errno(r, "Failed to process PropertiesChanged signal: %m");

        return 0;
}