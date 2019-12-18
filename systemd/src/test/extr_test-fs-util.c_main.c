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
 int /*<<< orphan*/  LOG_INFO ; 
 char* arg_test_dir ; 
 int /*<<< orphan*/  test_access_fd () ; 
 int /*<<< orphan*/  test_chase_symlinks () ; 
 int /*<<< orphan*/  test_chmod_and_chown () ; 
 int /*<<< orphan*/  test_dot_or_dot_dot () ; 
 int /*<<< orphan*/  test_fsync_directory_of_file () ; 
 int /*<<< orphan*/  test_get_files_in_directory () ; 
 int /*<<< orphan*/  test_readlink_and_make_absolute () ; 
 int /*<<< orphan*/  test_rename_noreplace () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_touch_file () ; 
 int /*<<< orphan*/  test_unlink_noerrno () ; 
 int /*<<< orphan*/  test_unlinkat_deallocate () ; 
 int /*<<< orphan*/  test_var_tmp () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_INFO);

        arg_test_dir = argv[1];

        test_chase_symlinks();
        test_unlink_noerrno();
        test_readlink_and_make_absolute();
        test_get_files_in_directory();
        test_var_tmp();
        test_dot_or_dot_dot();
        test_access_fd();
        test_touch_file();
        test_unlinkat_deallocate();
        test_fsync_directory_of_file();
        test_rename_noreplace();
        test_chmod_and_chown();

        return 0;
}