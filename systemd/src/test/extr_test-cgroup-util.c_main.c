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
 int /*<<< orphan*/  TEST_REQ_RUNNING_SYSTEMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_cg_get_keyed_attribute () ; 
 int /*<<< orphan*/  test_cg_tests () ; 
 int /*<<< orphan*/  test_controller_is_valid () ; 
 int /*<<< orphan*/  test_escape () ; 
 int /*<<< orphan*/  test_fd_is_cgroup_fs () ; 
 int /*<<< orphan*/  test_get_paths () ; 
 int /*<<< orphan*/  test_is_cgroup_fs () ; 
 int /*<<< orphan*/  test_mask_supported () ; 
 int /*<<< orphan*/  test_path_decode_unit () ; 
 int /*<<< orphan*/  test_path_get_owner_uid () ; 
 int /*<<< orphan*/  test_path_get_session () ; 
 int /*<<< orphan*/  test_path_get_slice () ; 
 int /*<<< orphan*/  test_path_get_unit () ; 
 int /*<<< orphan*/  test_path_get_user_slice () ; 
 int /*<<< orphan*/  test_path_get_user_unit () ; 
 int /*<<< orphan*/  test_proc () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_shift_path () ; 
 int /*<<< orphan*/  test_slice_to_path () ; 

int main(void) {
        test_setup_logging(LOG_DEBUG);

        test_path_decode_unit();
        test_path_get_unit();
        test_path_get_user_unit();
        test_path_get_session();
        test_path_get_owner_uid();
        test_path_get_slice();
        test_path_get_user_slice();
        TEST_REQ_RUNNING_SYSTEMD(test_get_paths());
        test_proc();
        TEST_REQ_RUNNING_SYSTEMD(test_escape());
        test_controller_is_valid();
        test_slice_to_path();
        test_shift_path();
        TEST_REQ_RUNNING_SYSTEMD(test_mask_supported());
        TEST_REQ_RUNNING_SYSTEMD(test_is_cgroup_fs());
        TEST_REQ_RUNNING_SYSTEMD(test_fd_is_cgroup_fs());
        test_cg_tests();
        test_cg_get_keyed_attribute();

        return 0;
}