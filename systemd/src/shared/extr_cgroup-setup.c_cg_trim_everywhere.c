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
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  scalar_t__ CGroupController ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_CONTROLLER_TO_MASK (scalar_t__) ; 
 int /*<<< orphan*/  CGROUP_MASK_EXTEND_JOINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGROUP_MASK_V1 ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 int cg_all_unified () ; 
 int cg_trim (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  cgroup_controller_to_string (scalar_t__) ; 

int cg_trim_everywhere(CGroupMask supported, const char *path, bool delete_root) {
        CGroupController c;
        CGroupMask done;
        int r, q;

        r = cg_trim(SYSTEMD_CGROUP_CONTROLLER, path, delete_root);
        if (r < 0)
                return r;

        q = cg_all_unified();
        if (q < 0)
                return q;
        if (q > 0)
                return r;

        supported &= CGROUP_MASK_V1;
        done = 0;

        for (c = 0; c < _CGROUP_CONTROLLER_MAX; c++) {
                CGroupMask bit = CGROUP_CONTROLLER_TO_MASK(c);

                if (!FLAGS_SET(supported, bit))
                        continue;

                if (FLAGS_SET(done, bit))
                        continue;

                (void) cg_trim(cgroup_controller_to_string(c), path, delete_root);
                done |= CGROUP_MASK_EXTEND_JOINED(bit);
        }

        return r;
}