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
struct TYPE_5__ {scalar_t__ result; } ;
typedef  scalar_t__ MountResult ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_MOUNTED ; 
 scalar_t__ MOUNT_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_enter_mounted(Mount *m, MountResult f) {
        assert(m);

        if (m->result == MOUNT_SUCCESS)
                m->result = f;

        mount_set_state(m, MOUNT_MOUNTED);
}