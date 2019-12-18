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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ bpf_firewall_compile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_firewall_install (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_firewall_load_custom (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_apply_firewall(Unit *u) {
        assert(u);

        /* Best-effort: let's apply IP firewalling and/or accounting if that's enabled */

        if (bpf_firewall_compile(u) < 0)
                return;

        (void) bpf_firewall_load_custom(u);
        (void) bpf_firewall_install(u);
}