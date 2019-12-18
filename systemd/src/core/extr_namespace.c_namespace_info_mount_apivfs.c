#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protect_kernel_tunables; scalar_t__ protect_control_groups; scalar_t__ mount_apivfs; } ;
typedef  TYPE_1__ NamespaceInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

__attribute__((used)) static bool namespace_info_mount_apivfs(const NamespaceInfo *ns_info) {
        assert(ns_info);

        /*
         * ProtectControlGroups= and ProtectKernelTunables= imply MountAPIVFS=,
         * since to protect the API VFS mounts, they need to be around in the
         * first place...
         */

        return ns_info->mount_apivfs ||
                ns_info->protect_control_groups ||
                ns_info->protect_kernel_tunables;
}