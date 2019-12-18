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
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 char* SYSTEMD_CGROUP_CONTROLLER_HYBRID ; 
 char* SYSTEMD_CGROUP_CONTROLLER_LEGACY ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ cg_hybrid_unified () ; 
 char* startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *controller_to_dirname(const char *controller) {
        const char *e;

        assert(controller);

        /* Converts a controller name to the directory name below
         * /sys/fs/cgroup/ we want to mount it to. Effectively, this
         * just cuts off the name= prefixed used for named
         * hierarchies, if it is specified. */

        if (streq(controller, SYSTEMD_CGROUP_CONTROLLER)) {
                if (cg_hybrid_unified() > 0)
                        controller = SYSTEMD_CGROUP_CONTROLLER_HYBRID;
                else
                        controller = SYSTEMD_CGROUP_CONTROLLER_LEGACY;
        }

        e = startswith(controller, "name=");
        if (e)
                return e;

        return controller;
}