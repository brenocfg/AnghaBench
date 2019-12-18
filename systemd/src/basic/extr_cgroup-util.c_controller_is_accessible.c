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

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int cg_all_unified () ; 
 int /*<<< orphan*/  cg_controller_is_valid (char const*) ; 
 char* controller_to_dirname (char const*) ; 
 int errno ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 
 char* strjoina (char*,char const*) ; 

__attribute__((used)) static int controller_is_accessible(const char *controller) {
        int r;

        assert(controller);

        /* Checks whether a specific controller is accessible,
         * i.e. its hierarchy mounted. In the unified hierarchy all
         * controllers are considered accessible, except for the named
         * hierarchies */

        if (!cg_controller_is_valid(controller))
                return -EINVAL;

        r = cg_all_unified();
        if (r < 0)
                return r;
        if (r > 0) {
                /* We don't support named hierarchies if we are using
                 * the unified hierarchy. */

                if (streq(controller, SYSTEMD_CGROUP_CONTROLLER))
                        return 0;

                if (startswith(controller, "name="))
                        return -EOPNOTSUPP;

        } else {
                const char *cc, *dn;

                dn = controller_to_dirname(controller);
                cc = strjoina("/sys/fs/cgroup/", dn);

                if (laccess(cc, F_OK) < 0)
                        return -errno;
        }

        return 0;
}