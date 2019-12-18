#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int reset_accounting; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bpf_firewall_load_custom (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_export_state_files (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_realize_cgroup (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_reset_accounting (TYPE_1__*) ; 
 int unit_setup_dynamic_creds (TYPE_1__*) ; 
 int unit_setup_exec_runtime (TYPE_1__*) ; 

int unit_prepare_exec(Unit *u) {
        int r;

        assert(u);

        /* Load any custom firewall BPF programs here once to test if they are existing and actually loadable.
         * Fail here early since later errors in the call chain unit_realize_cgroup to cgroup_context_apply are ignored. */
        r = bpf_firewall_load_custom(u);
        if (r < 0)
                return r;

        /* Prepares everything so that we can fork of a process for this unit */

        (void) unit_realize_cgroup(u);

        if (u->reset_accounting) {
                (void) unit_reset_accounting(u);
                u->reset_accounting = false;
        }

        unit_export_state_files(u);

        r = unit_setup_exec_runtime(u);
        if (r < 0)
                return r;

        r = unit_setup_dynamic_creds(u);
        if (r < 0)
                return r;

        return 0;
}