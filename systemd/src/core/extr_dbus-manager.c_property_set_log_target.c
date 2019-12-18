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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  Manager ;
typedef  scalar_t__ LogTarget ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ log_target_from_string (char const*) ; 
 int /*<<< orphan*/  manager_override_log_target (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  manager_restore_original_log_target (int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static int property_set_log_target(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *value,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        const char *t;
        int r;

        assert(bus);
        assert(value);

        r = sd_bus_message_read(value, "s", &t);
        if (r < 0)
                return r;

        if (isempty(t))
                manager_restore_original_log_target(m);
        else {
                LogTarget target;

                target = log_target_from_string(t);
                if (target < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid log target '%s'", t);

                manager_override_log_target(m, target);
        }

        return 0;
}