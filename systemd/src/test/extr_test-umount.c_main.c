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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_mount_points_list (char*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_swap_list (char*) ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_DEBUG);

        test_mount_points_list(NULL);
        test_mount_points_list("/test-umount/empty.mountinfo");
        test_mount_points_list("/test-umount/garbled.mountinfo");
        test_mount_points_list("/test-umount/rhbug-1554943.mountinfo");

        test_swap_list(NULL);
        test_swap_list("/test-umount/example.swaps");
}