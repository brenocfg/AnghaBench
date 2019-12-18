#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ result; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/  exec_context; int /*<<< orphan*/  exec_runtime; } ;
typedef  scalar_t__ MountResult ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_DEAD ; 
 int /*<<< orphan*/  MOUNT_FAILED ; 
 scalar_t__ MOUNT_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_creds_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mount_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  mount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_destroy_runtime_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_remove_dependencies (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_unref_uid_gid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mount_enter_dead(Mount *m, MountResult f) {
        assert(m);

        if (m->result == MOUNT_SUCCESS)
                m->result = f;

        unit_log_result(UNIT(m), m->result == MOUNT_SUCCESS, mount_result_to_string(m->result));
        mount_set_state(m, m->result != MOUNT_SUCCESS ? MOUNT_FAILED : MOUNT_DEAD);

        m->exec_runtime = exec_runtime_unref(m->exec_runtime, true);

        unit_destroy_runtime_directory(UNIT(m), &m->exec_context);

        unit_unref_uid_gid(UNIT(m), true);

        dynamic_creds_destroy(&m->dynamic_creds);

        /* Any dependencies based on /proc/self/mountinfo are now stale */
        unit_remove_dependencies(UNIT(m), UNIT_DEPENDENCY_MOUNTINFO_IMPLICIT);
}