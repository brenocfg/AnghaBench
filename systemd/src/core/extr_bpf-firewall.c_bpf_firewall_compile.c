#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; void* ip_bpf_egress; void* ip_bpf_ingress; int /*<<< orphan*/  ip_accounting_egress_map_fd; int /*<<< orphan*/  ip_accounting_ingress_map_fd; void* ipv6_deny_map_fd; void* ipv4_deny_map_fd; void* ipv6_allow_map_fd; void* ipv4_allow_map_fd; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_13__ {int /*<<< orphan*/  ip_accounting; } ;
typedef  TYPE_2__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ALLOWED ; 
 int /*<<< orphan*/  ACCESS_DENIED ; 
 int BPF_FIREWALL_SUPPORTED_WITH_MULTI ; 
 int BPF_FIREWALL_UNSUPPORTED ; 
 int EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bpf_firewall_compile_bpf (TYPE_1__*,int,void**,int,int) ; 
 int bpf_firewall_prepare_access_maps (TYPE_1__*,int /*<<< orphan*/ ,void**,void**,int*) ; 
 int bpf_firewall_prepare_accounting_maps (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bpf_firewall_supported () ; 
 void* bpf_program_unref (void*) ; 
 int log_unit_debug_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int log_unit_error_errno (TYPE_1__*,int,char*) ; 
 void* safe_close (void*) ; 
 TYPE_2__* unit_get_cgroup_context (TYPE_1__*) ; 

int bpf_firewall_compile(Unit *u) {
        CGroupContext *cc;
        int r, supported;
        bool ip_allow_any = false, ip_deny_any = false;

        assert(u);

        cc = unit_get_cgroup_context(u);
        if (!cc)
                return -EINVAL;

        supported = bpf_firewall_supported();
        if (supported < 0)
                return supported;
        if (supported == BPF_FIREWALL_UNSUPPORTED)
                return log_unit_debug_errno(u, SYNTHETIC_ERRNO(EOPNOTSUPP),
                                            "BPF firewalling not supported on this manager, proceeding without.");
        if (supported != BPF_FIREWALL_SUPPORTED_WITH_MULTI && u->type == UNIT_SLICE)
                /* If BPF_F_ALLOW_MULTI is not supported we don't support any BPF magic on inner nodes (i.e. on slice
                 * units), since that would mean leaf nodes couldn't do any BPF anymore at all. Under the assumption
                 * that BPF is more interesting on leaf nodes we hence avoid it on inner nodes in that case. This is
                 * consistent with old systemd behaviour from before v238, where BPF wasn't supported in inner nodes at
                 * all, either. */
                return log_unit_debug_errno(u, SYNTHETIC_ERRNO(EOPNOTSUPP),
                                            "BPF_F_ALLOW_MULTI is not supported on this manager, not doing BPF firewall on slice units.");

        /* Note that when we compile a new firewall we first flush out the access maps and the BPF programs themselves,
         * but we reuse the the accounting maps. That way the firewall in effect always maps to the actual
         * configuration, but we don't flush out the accounting unnecessarily */

        u->ip_bpf_ingress = bpf_program_unref(u->ip_bpf_ingress);
        u->ip_bpf_egress = bpf_program_unref(u->ip_bpf_egress);

        u->ipv4_allow_map_fd = safe_close(u->ipv4_allow_map_fd);
        u->ipv4_deny_map_fd = safe_close(u->ipv4_deny_map_fd);

        u->ipv6_allow_map_fd = safe_close(u->ipv6_allow_map_fd);
        u->ipv6_deny_map_fd = safe_close(u->ipv6_deny_map_fd);

        if (u->type != UNIT_SLICE) {
                /* In inner nodes we only do accounting, we do not actually bother with access control. However, leaf
                 * nodes will incorporate all IP access rules set on all their parent nodes. This has the benefit that
                 * they can optionally cancel out system-wide rules. Since inner nodes can't contain processes this
                 * means that all configure IP access rules *will* take effect on processes, even though we never
                 * compile them for inner nodes. */

                r = bpf_firewall_prepare_access_maps(u, ACCESS_ALLOWED, &u->ipv4_allow_map_fd, &u->ipv6_allow_map_fd, &ip_allow_any);
                if (r < 0)
                        return log_unit_error_errno(u, r, "Preparation of eBPF allow maps failed: %m");

                r = bpf_firewall_prepare_access_maps(u, ACCESS_DENIED, &u->ipv4_deny_map_fd, &u->ipv6_deny_map_fd, &ip_deny_any);
                if (r < 0)
                        return log_unit_error_errno(u, r, "Preparation of eBPF deny maps failed: %m");
        }

        r = bpf_firewall_prepare_accounting_maps(u, cc->ip_accounting, &u->ip_accounting_ingress_map_fd, &u->ip_accounting_egress_map_fd);
        if (r < 0)
                return log_unit_error_errno(u, r, "Preparation of eBPF accounting maps failed: %m");

        r = bpf_firewall_compile_bpf(u, true, &u->ip_bpf_ingress, ip_allow_any, ip_deny_any);
        if (r < 0)
                return log_unit_error_errno(u, r, "Compilation for ingress BPF program failed: %m");

        r = bpf_firewall_compile_bpf(u, false, &u->ip_bpf_egress, ip_allow_any, ip_deny_any);
        if (r < 0)
                return log_unit_error_errno(u, r, "Compilation for egress BPF program failed: %m");

        return 0;
}