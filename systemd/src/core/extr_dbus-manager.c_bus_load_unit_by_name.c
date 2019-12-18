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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/ * Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int bus_get_unit_by_name (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 int manager_load_unit (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int bus_load_unit_by_name(Manager *m, sd_bus_message *message, const char *name, Unit **ret_unit, sd_bus_error *error) {
        assert(m);
        assert(message);
        assert(ret_unit);

        /* Pretty much the same as bus_get_unit_by_name(), but we also load the unit if necessary. */

        if (isempty(name))
                return bus_get_unit_by_name(m, message, name, ret_unit, error);

        return manager_load_unit(m, name, NULL, error, ret_unit);
}