#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int reset_accounting; } ;
struct TYPE_6__ {int /*<<< orphan*/  exec_command; void* reload_result; void* result; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 void* MOUNT_SUCCESS ; 
 TYPE_4__* UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  _MOUNT_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  exec_command_reset_status_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_cycle_clear(Mount *m) {
        assert(m);

        /* Clear all state we shall forget for this new cycle */

        m->result = MOUNT_SUCCESS;
        m->reload_result = MOUNT_SUCCESS;
        exec_command_reset_status_array(m->exec_command, _MOUNT_EXEC_COMMAND_MAX);
        UNIT(m)->reset_accounting = true;
}