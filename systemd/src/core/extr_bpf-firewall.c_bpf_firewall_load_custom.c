#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ip_bpf_custom_egress; int /*<<< orphan*/  ip_bpf_custom_ingress; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_10__ {scalar_t__ ip_filters_egress; scalar_t__ ip_filters_ingress; } ;
typedef  TYPE_2__ CGroupContext ;

/* Variables and functions */
 int BPF_FIREWALL_SUPPORTED_WITH_MULTI ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bpf_firewall_supported () ; 
 int load_bpf_progs_from_fs_to_set (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int log_unit_debug_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* unit_get_cgroup_context (TYPE_1__*) ; 

int bpf_firewall_load_custom(Unit *u) {
        CGroupContext *cc;
        int r, supported;

        assert(u);

        cc = unit_get_cgroup_context(u);
        if (!cc)
                return 0;

        if (!(cc->ip_filters_ingress || cc->ip_filters_egress))
                return 0;

        supported = bpf_firewall_supported();
        if (supported < 0)
                return supported;

        if (supported != BPF_FIREWALL_SUPPORTED_WITH_MULTI)
                return log_unit_debug_errno(u, SYNTHETIC_ERRNO(EOPNOTSUPP), "BPF_F_ALLOW_MULTI not supported on this manager, cannot attach custom BPF programs.");

        r = load_bpf_progs_from_fs_to_set(u, cc->ip_filters_ingress, &u->ip_bpf_custom_ingress);
        if (r < 0)
                return r;
        r = load_bpf_progs_from_fs_to_set(u, cc->ip_filters_egress, &u->ip_bpf_custom_egress);
        if (r < 0)
                return r;

        return 0;
}