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
 int /*<<< orphan*/  test_device_major_minor_valid () ; 
 int /*<<< orphan*/  test_device_path_make_canonical () ; 
 int /*<<< orphan*/  test_fd_is_network_ns () ; 
 int /*<<< orphan*/  test_files_same () ; 
 int /*<<< orphan*/  test_is_symlink () ; 
 int /*<<< orphan*/  test_path_is_fs_type () ; 
 int /*<<< orphan*/  test_path_is_temporary_fs () ; 

int main(int argc, char *argv[]) {
        test_files_same();
        test_is_symlink();
        test_path_is_fs_type();
        test_path_is_temporary_fs();
        test_fd_is_network_ns();
        test_device_major_minor_valid();
        test_device_path_make_canonical();

        return 0;
}