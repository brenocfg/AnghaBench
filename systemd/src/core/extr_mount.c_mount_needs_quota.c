#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  options; scalar_t__ fstype; } ;
typedef  TYPE_1__ MountParameters ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int fstab_test_option (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fstype_is_network (scalar_t__) ; 
 scalar_t__ mount_is_bind (TYPE_1__ const*) ; 

__attribute__((used)) static bool mount_needs_quota(const MountParameters *p) {
        assert(p);

        /* Quotas are not enabled on network filesystems, but we want them, for example, on storage connected via
         * iscsi. We hence don't use mount_is_network() here, as that would also return true for _netdev devices. */
        if (p->fstype && fstype_is_network(p->fstype))
                return false;

        if (mount_is_bind(p))
                return false;

        return fstab_test_option(p->options,
                                 "usrquota\0" "grpquota\0" "quota\0" "usrjquota\0" "grpjquota\0");
}