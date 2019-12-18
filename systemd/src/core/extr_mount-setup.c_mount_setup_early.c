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

/* Variables and functions */
 scalar_t__ ELEMENTSOF (int /*<<< orphan*/ ) ; 
 scalar_t__ N_EARLY_MOUNT ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int mount_points_setup (scalar_t__,int) ; 
 int /*<<< orphan*/  mount_table ; 

int mount_setup_early(void) {
        assert_cc(N_EARLY_MOUNT <= ELEMENTSOF(mount_table));

        /* Do a minimal mount of /proc and friends to enable the most
         * basic stuff, such as SELinux */
        return mount_points_setup(N_EARLY_MOUNT, false);
}