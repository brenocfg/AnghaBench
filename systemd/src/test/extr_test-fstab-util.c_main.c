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
 int /*<<< orphan*/  test_fstab_filter_options () ; 
 int /*<<< orphan*/  test_fstab_find_pri () ; 
 int /*<<< orphan*/  test_fstab_node_to_udev_node () ; 
 int /*<<< orphan*/  test_fstab_yes_no_option () ; 

int main(void) {
        test_fstab_filter_options();
        test_fstab_find_pri();
        test_fstab_yes_no_option();
        test_fstab_node_to_udev_node();

        return 0;
}