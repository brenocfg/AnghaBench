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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  JobType ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_unit_method_start_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int manager_load_unit (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static int method_start_unit_generic(sd_bus_message *message, Manager *m, JobType job_type, bool reload_if_possible, sd_bus_error *error) {
        const char *name;
        Unit *u;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "s", &name);
        if (r < 0)
                return r;

        r = manager_load_unit(m, name, NULL, error, &u);
        if (r < 0)
                return r;

        return bus_unit_method_start_generic(message, u, job_type, reload_if_possible, error);
}