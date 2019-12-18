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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  unit_write_settingf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*,char const*,...) ; 

__attribute__((used)) static int bus_set_transient_exit_status(
                Unit *u,
                const char *name,
                int *p,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        int32_t k;
        int r;

        assert(p);

        r = sd_bus_message_read(message, "i", &k);
        if (r < 0)
                return r;

        if (k > 255)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Exit status must be in range 0…255 or negative.");

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                *p = k < 0 ? -1 : k;

                if (k < 0)
                        unit_write_settingf(u, flags, name, "%s=", name);
                else
                        unit_write_settingf(u, flags, name, "%s=%i", name, k);
        }

        return 1;
}