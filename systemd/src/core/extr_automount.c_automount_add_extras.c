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
typedef  int /*<<< orphan*/  Automount ;

/* Variables and functions */
 int automount_add_default_dependencies (int /*<<< orphan*/ *) ; 
 int automount_add_mount_dependencies (int /*<<< orphan*/ *) ; 
 int automount_add_trigger_dependencies (int /*<<< orphan*/ *) ; 
 int automount_set_where (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int automount_add_extras(Automount *a) {
        int r;

        r = automount_set_where(a);
        if (r < 0)
                return r;

        r = automount_add_trigger_dependencies(a);
        if (r < 0)
                return r;

        r = automount_add_mount_dependencies(a);
        if (r < 0)
                return r;

        return automount_add_default_dependencies(a);
}