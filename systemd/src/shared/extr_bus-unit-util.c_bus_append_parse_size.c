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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int bus_log_create_error (int) ; 
 int log_error_errno (int,char*,char const*,char const*) ; 
 int parse_size (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bus_append_parse_size(sd_bus_message *m, const char *field, const char *eq, uint64_t base) {
        uint64_t v;
        int r;

        r = parse_size(eq, base, &v);
        if (r < 0)
                return log_error_errno(r, "Failed to parse %s=%s: %m", field, eq);

        r = sd_bus_message_append(m, "(sv)", field, "t", v);
        if (r < 0)
                return bus_log_create_error(r);

        return 1;
}