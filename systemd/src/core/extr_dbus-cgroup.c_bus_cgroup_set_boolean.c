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
typedef  int /*<<< orphan*/  UnitWriteFlags ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_WRITE_FLAGS_NOOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  unit_invalidate_cgroup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_write_settingf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yes_no (int) ; 

__attribute__((used)) static int bus_cgroup_set_boolean(
                Unit *u,
                const char *name,
                bool *p,
                CGroupMask mask,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        int b, r;

        assert(p);

        r = sd_bus_message_read(message, "b", &b);
        if (r < 0)
                return r;

        if (!UNIT_WRITE_FLAGS_NOOP(flags)) {
                *p = b;
                unit_invalidate_cgroup(u, mask);
                unit_write_settingf(u, flags, name, "%s=%s", name, yes_no(b));
        }

        return 1;
}