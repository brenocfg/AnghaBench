#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_7__ {int /*<<< orphan*/  result; int /*<<< orphan*/  where; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTOMOUNT_DEAD ; 
 int /*<<< orphan*/  AUTOMOUNT_FAILED ; 
 int /*<<< orphan*/  AUTOMOUNT_FAILURE_START_LIMIT_HIT ; 
 int /*<<< orphan*/  AUTOMOUNT_SUCCESS ; 
 int EEXIST ; 
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  automount_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  automount_enter_waiting (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_mount_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unit_acquire_invocation_id (int /*<<< orphan*/ *) ; 
 int unit_test_start_limit (int /*<<< orphan*/ *) ; 
 int unit_test_trigger_loaded (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int automount_start(Unit *u) {
        Automount *a = AUTOMOUNT(u);
        int r;

        assert(a);
        assert(IN_SET(a->state, AUTOMOUNT_DEAD, AUTOMOUNT_FAILED));

        if (path_is_mount_point(a->where, NULL, 0) > 0) {
                log_unit_error(u, "Path %s is already a mount point, refusing start.", a->where);
                return -EEXIST;
        }

        r = unit_test_trigger_loaded(u);
        if (r < 0)
                return r;

        r = unit_test_start_limit(u);
        if (r < 0) {
                automount_enter_dead(a, AUTOMOUNT_FAILURE_START_LIMIT_HIT);
                return r;
        }

        r = unit_acquire_invocation_id(u);
        if (r < 0)
                return r;

        a->result = AUTOMOUNT_SUCCESS;
        automount_enter_waiting(a);
        return 1;
}