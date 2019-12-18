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
 int bus_log_create_error (int) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char const*,char*,char const*) ; 

__attribute__((used)) static int bus_append_string(sd_bus_message *m, const char *field, const char *eq) {
        int r;

        r = sd_bus_message_append(m, "(sv)", field, "s", eq);
        if (r < 0)
                return bus_log_create_error(r);

        return 1;
}