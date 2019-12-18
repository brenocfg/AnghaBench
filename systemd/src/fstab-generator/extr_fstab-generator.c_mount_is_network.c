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
struct mntent {int /*<<< orphan*/  mnt_type; int /*<<< orphan*/  mnt_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct mntent*) ; 
 scalar_t__ fstab_test_option (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fstype_is_network (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mount_is_network(struct mntent *me) {
        assert(me);

        return fstab_test_option(me->mnt_opts, "_netdev\0") ||
               fstype_is_network(me->mnt_type);
}