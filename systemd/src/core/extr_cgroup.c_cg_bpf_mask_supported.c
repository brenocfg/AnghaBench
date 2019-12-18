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

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_MASK_BPF_DEVICES ; 
 int /*<<< orphan*/  CGROUP_MASK_BPF_FIREWALL ; 
 int bpf_devices_supported () ; 
 int bpf_firewall_supported () ; 

__attribute__((used)) static int cg_bpf_mask_supported(CGroupMask *ret) {
        CGroupMask mask = 0;
        int r;

        /* BPF-based firewall */
        r = bpf_firewall_supported();
        if (r > 0)
                mask |= CGROUP_MASK_BPF_FIREWALL;

        /* BPF-based device access control */
        r = bpf_devices_supported();
        if (r > 0)
                mask |= CGROUP_MASK_BPF_DEVICES;

        *ret = mask;
        return 0;
}