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
 char const* SYSTEMD_CGROUP_CONTROLLER ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 int cg_all_unified () ; 
 int cg_create (char const*,char const*) ; 
 int /*<<< orphan*/  cg_trim (char const*,char const*,int) ; 
 char* cgroup_controller_to_string (scalar_t__) ; 

int cg_create_everywhere(CGroupMask supported, CGroupMask mask, const char *path) {
        CGroupController c;
        CGroupMask done;
        bool created;
        int r;

        /* This one will create a cgroup in our private tree, but also
         * duplicate it in the trees specified in mask, and remove it
         * in all others.
         *
         * Returns 0 if the group already existed in the systemd hierarchy,
         * 1 on success, negative otherwise.
         */

        /* First create the cgroup in our own hierarchy. */
        r = cg_create(SYSTEMD_CGROUP_CONTROLLER, path);
        if (r < 0)
                return r;
        created = r;

        /* If we are in the unified hierarchy, we are done now */
        r = cg_all_unified();
        if (r < 0)
                return r;
        if (r > 0)
                return created;

        supported &= CGROUP_MASK_V1;
        mask = CGROUP_MASK_EXTEND_JOINED(mask);
        done = 0;

        /* Otherwise, do the same in the other hierarchies */
        for (c = 0; c < _CGROUP_CONTROLLER_MAX; c++) {
                CGroupMask bit = CGROUP_CONTROLLER_TO_MASK(c);
                const char *n;

                if (!FLAGS_SET(supported, bit))
                        continue;

                if (FLAGS_SET(done, bit))
                        continue;

                n = cgroup_controller_to_string(c);
                if (FLAGS_SET(mask, bit))
                        (void) cg_create(n, path);
                else
                        (void) cg_trim(n, path, true);

                done |= CGROUP_MASK_EXTEND_JOINED(bit);
        }

        return created;
}