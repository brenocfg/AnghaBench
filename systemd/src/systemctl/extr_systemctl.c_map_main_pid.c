#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {int running; scalar_t__ main_pid; } ;
typedef  TYPE_1__ UnitStatusInfo ;

/* Variables and functions */
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static int map_main_pid(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        UnitStatusInfo *i = userdata;
        uint32_t u;
        int r;

        r = sd_bus_message_read(m, "u", &u);
        if (r < 0)
                return r;

        i->main_pid = (pid_t) u;
        i->running = u > 0;

        return 0;
}