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
typedef  int (* sd_bus_message_handler_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  GenericUnitOperationFlags ;

/* Variables and functions */
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_UNIT_LOAD ; 
 int /*<<< orphan*/  GENERIC_UNIT_VALIDATE_LOADED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_get_unit_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int bus_unit_validate_load_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isempty (char const*) ; 
 int manager_load_unit (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static int method_generic_unit_operation(
                sd_bus_message *message,
                Manager *m,
                sd_bus_error *error,
                sd_bus_message_handler_t handler,
                GenericUnitOperationFlags flags) {

        const char *name;
        Unit *u;
        int r;

        assert(message);
        assert(m);

        /* Read the first argument from the command and pass the operation to the specified per-unit
         * method. */

        r = sd_bus_message_read(message, "s", &name);
        if (r < 0)
                return r;

        if (!isempty(name) && FLAGS_SET(flags, GENERIC_UNIT_LOAD))
                r = manager_load_unit(m, name, NULL, error, &u);
        else
                r = bus_get_unit_by_name(m, message, name, &u, error);
        if (r < 0)
                return r;

        if (FLAGS_SET(flags, GENERIC_UNIT_VALIDATE_LOADED)) {
                r = bus_unit_validate_load_state(u, error);
                if (r < 0)
                        return r;
        }

        return handler(message, u, error);
}