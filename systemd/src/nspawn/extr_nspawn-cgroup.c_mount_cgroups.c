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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ CGroupUnified ;

/* Variables and functions */
 scalar_t__ CGROUP_UNIFIED_ALL ; 
 int mount_legacy_cgns_supported (char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int mount_legacy_cgns_unsupported (char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int mount_unified_cgroups (char const*) ; 

int mount_cgroups(
                const char *dest,
                CGroupUnified unified_requested,
                bool userns,
                uid_t uid_shift,
                uid_t uid_range,
                const char *selinux_apifs_context,
                bool use_cgns) {

        if (unified_requested >= CGROUP_UNIFIED_ALL)
                return mount_unified_cgroups(dest);
        if (use_cgns)
                return mount_legacy_cgns_supported(dest, unified_requested, userns, uid_shift, uid_range, selinux_apifs_context);

        return mount_legacy_cgns_unsupported(dest, unified_requested, userns, uid_shift, uid_range, selinux_apifs_context);
}