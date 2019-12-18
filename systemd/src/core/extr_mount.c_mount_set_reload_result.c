#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ reload_result; } ;
typedef  scalar_t__ MountResult ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 scalar_t__ MOUNT_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void mount_set_reload_result(Mount *m, MountResult result) {
        assert(m);

        /* Only store the first error we encounter */
        if (m->reload_result != MOUNT_SUCCESS)
                return;

        m->reload_result = result;
}