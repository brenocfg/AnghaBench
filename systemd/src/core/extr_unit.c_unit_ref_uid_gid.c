#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_3__ {int remove_ipc; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_unit_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 TYPE_1__* unit_get_exec_context (int /*<<< orphan*/ *) ; 
 int unit_ref_uid_gid_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int unit_ref_uid_gid(Unit *u, uid_t uid, gid_t gid) {
        ExecContext *c;
        int r;

        assert(u);

        c = unit_get_exec_context(u);

        r = unit_ref_uid_gid_internal(u, uid, gid, c ? c->remove_ipc : false);
        if (r < 0)
                return log_unit_warning_errno(u, r, "Couldn't add UID/GID reference to unit, proceeding without: %m");

        return r;
}