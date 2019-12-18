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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  MS_PRIVATE ; 
 int /*<<< orphan*/  MS_SHARED ; 
 int /*<<< orphan*/  MS_SLAVE ; 
 int /*<<< orphan*/  test_mnt_id () ; 
 int /*<<< orphan*/  test_mount_propagation_flags (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_path_is_mount_point () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_mount_propagation_flags("shared", 0, MS_SHARED);
        test_mount_propagation_flags("slave", 0, MS_SLAVE);
        test_mount_propagation_flags("private", 0, MS_PRIVATE);
        test_mount_propagation_flags(NULL, 0, 0);
        test_mount_propagation_flags("", 0, 0);
        test_mount_propagation_flags("xxxx", -EINVAL, 0);
        test_mount_propagation_flags(" ", -EINVAL, 0);

        test_mnt_id();
        test_path_is_mount_point();

        return 0;
}