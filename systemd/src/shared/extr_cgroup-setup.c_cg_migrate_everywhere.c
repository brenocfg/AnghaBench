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
typedef  char* (* cg_migrate_callback_t ) (int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  scalar_t__ CGroupController ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_CONTROLLER_TO_MASK (scalar_t__) ; 
 int /*<<< orphan*/  CGROUP_MASK_EXTEND_JOINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGROUP_MASK_V1 ; 
 int /*<<< orphan*/  CGROUP_REMOVE ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 int cg_all_unified () ; 
 int cg_migrate_recursive (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cg_migrate_recursive_fallback (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_controller_to_string (scalar_t__) ; 
 int /*<<< orphan*/  path_equal (char const*,char const*) ; 

int cg_migrate_everywhere(CGroupMask supported, const char *from, const char *to, cg_migrate_callback_t to_callback, void *userdata) {
        CGroupController c;
        CGroupMask done;
        int r = 0, q;

        if (!path_equal(from, to))  {
                r = cg_migrate_recursive(SYSTEMD_CGROUP_CONTROLLER, from, SYSTEMD_CGROUP_CONTROLLER, to, CGROUP_REMOVE);
                if (r < 0)
                        return r;
        }

        q = cg_all_unified();
        if (q < 0)
                return q;
        if (q > 0)
                return r;

        supported &= CGROUP_MASK_V1;
        done = 0;

        for (c = 0; c < _CGROUP_CONTROLLER_MAX; c++) {
                CGroupMask bit = CGROUP_CONTROLLER_TO_MASK(c);
                const char *p = NULL;

                if (!FLAGS_SET(supported, bit))
                        continue;

                if (FLAGS_SET(done, bit))
                        continue;

                if (to_callback)
                        p = to_callback(bit, userdata);
                if (!p)
                        p = to;

                (void) cg_migrate_recursive_fallback(SYSTEMD_CGROUP_CONTROLLER, to, cgroup_controller_to_string(c), p, 0);
                done |= CGROUP_MASK_EXTEND_JOINED(bit);
        }

        return r;
}