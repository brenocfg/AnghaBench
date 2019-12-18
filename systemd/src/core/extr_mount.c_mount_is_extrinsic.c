#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  manager; } ;
struct TYPE_10__ {int /*<<< orphan*/  where; } ;
struct TYPE_9__ {int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ MountParameters ;
typedef  TYPE_2__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 scalar_t__ PATH_IN_SET (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ PATH_STARTSWITH_SET (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 TYPE_7__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ fstab_test_option (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* get_mount_parameters (TYPE_2__*) ; 
 int /*<<< orphan*/  in_initrd () ; 

__attribute__((used)) static bool mount_is_extrinsic(Mount *m) {
        MountParameters *p;
        assert(m);

        /* Returns true for all units that are "magic" and should be excluded from the usual start-up and shutdown
         * dependencies. We call them "extrinsic" here, as they are generally mounted outside of the systemd dependency
         * logic. We shouldn't attempt to manage them ourselves but it's fine if the user operates on them with us. */

        if (!MANAGER_IS_SYSTEM(UNIT(m)->manager)) /* We only automatically manage mounts if we are in system mode */
                return true;

        if (PATH_IN_SET(m->where,  /* Don't bother with the OS data itself */
                        "/",
                        "/usr"))
                return true;

        if (PATH_STARTSWITH_SET(m->where,
                                "/run/initramfs",    /* This should stay around from before we boot until after we shutdown */
                                "/proc",             /* All of this is API VFS */
                                "/sys",              /* … dito … */
                                "/dev"))             /* … dito … */
                return true;

        /* If this is an initrd mount, and we are not in the initrd, then leave this around forever, too. */
        p = get_mount_parameters(m);
        if (p && fstab_test_option(p->options, "x-initrd.mount\0") && !in_initrd())
                return true;

        return false;
}