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
struct TYPE_5__ {int /*<<< orphan*/  cgroup_path; int /*<<< orphan*/  invocation_id; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int SD_ID128_STRING_MAX ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int cg_set_xattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cgroup_xattr_apply(Unit *u) {
        char ids[SD_ID128_STRING_MAX];
        int r;

        assert(u);

        if (!MANAGER_IS_SYSTEM(u->manager))
                return;

        if (sd_id128_is_null(u->invocation_id))
                return;

        r = cg_set_xattr(SYSTEMD_CGROUP_CONTROLLER, u->cgroup_path,
                         "trusted.invocation_id",
                         sd_id128_to_string(u->invocation_id, ids), 32,
                         0);
        if (r < 0)
                log_unit_debug_errno(u, r, "Failed to set invocation ID on control group %s, ignoring: %m", u->cgroup_path);
}