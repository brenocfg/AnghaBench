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
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int path_add_default_dependencies (int /*<<< orphan*/ *) ; 
 int path_add_mount_dependencies (int /*<<< orphan*/ *) ; 
 int path_add_trigger_dependencies (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int path_add_extras(Path *p) {
        int r;

        r = path_add_trigger_dependencies(p);
        if (r < 0)
                return r;

        r = path_add_mount_dependencies(p);
        if (r < 0)
                return r;

        return path_add_default_dependencies(p);
}