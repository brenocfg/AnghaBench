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
struct mntent {int /*<<< orphan*/  mnt_dir; int /*<<< orphan*/  mnt_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct mntent*) ; 
 scalar_t__ fstab_test_option (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool mount_in_initrd(struct mntent *me) {
        assert(me);

        return fstab_test_option(me->mnt_opts, "x-initrd.mount\0") ||
               streq(me->mnt_dir, "/usr");
}