#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitWriteFlags ;
struct TYPE_4__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  EmergencyAction ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int parse_emergency_action (char const*,int,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  unit_write_settingf (TYPE_1__*,int /*<<< orphan*/ ,char const*,char*,char const*,char const*) ; 

__attribute__((used)) static int bus_set_transient_emergency_action(
                Unit *u,
                const char *name,
                EmergencyAction *p,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        const char *s;
        EmergencyAction v;
        int r;
        bool system;

        assert(p);

        r = sd_bus_message_read(message, "s", &s);
        if (r < 0)
                return r;

        system = MANAGER_IS_SYSTEM(u->manager);
        r = parse_emergency_action(s, system, &v);
        if (r < 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS,
                                         r == -EOPNOTSUPP ? "%s setting invalid for manager type: %s"
                                                          : "Invalid %s setting: %s",
                                         name, s);

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                *p = v;
                unit_write_settingf(u, flags, name,
                                    "%s=%s", name, s);
        }

        return 1;
}