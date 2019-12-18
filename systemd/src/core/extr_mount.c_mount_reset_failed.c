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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ state; void* clean_result; void* reload_result; void* result; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOUNT_DEAD ; 
 scalar_t__ MOUNT_FAILED ; 
 void* MOUNT_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_reset_failed(Unit *u) {
        Mount *m = MOUNT(u);

        assert(m);

        if (m->state == MOUNT_FAILED)
                mount_set_state(m, MOUNT_DEAD);

        m->result = MOUNT_SUCCESS;
        m->reload_result = MOUNT_SUCCESS;
        m->clean_result = MOUNT_SUCCESS;
}