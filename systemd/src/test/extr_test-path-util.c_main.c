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
 int /*<<< orphan*/  test_empty_or_root () ; 
 int /*<<< orphan*/  test_file_in_same_dir () ; 
 int /*<<< orphan*/  test_filename_is_valid () ; 
 int /*<<< orphan*/  test_find_binary (char*) ; 
 int /*<<< orphan*/  test_fsck_exists () ; 
 int /*<<< orphan*/  test_hidden_or_backup_file () ; 
 int /*<<< orphan*/  test_last_path_component () ; 
 int /*<<< orphan*/  test_make_relative () ; 
 int /*<<< orphan*/  test_path () ; 
 int /*<<< orphan*/  test_path_equal_root () ; 
 int /*<<< orphan*/  test_path_extract_filename () ; 
 int /*<<< orphan*/  test_path_join () ; 
 int /*<<< orphan*/  test_path_startswith () ; 
 int /*<<< orphan*/  test_path_startswith_set () ; 
 int /*<<< orphan*/  test_path_startswith_strv () ; 
 int /*<<< orphan*/  test_prefix_root () ; 
 int /*<<< orphan*/  test_prefixes () ; 
 int /*<<< orphan*/  test_print_paths () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_skip_dev_prefix () ; 
 int /*<<< orphan*/  test_strv_resolve () ; 
 int /*<<< orphan*/  test_systemd_installation_has_version (char*) ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_DEBUG);

        test_print_paths();
        test_path();
        test_path_equal_root();
        test_find_binary(argv[0]);
        test_prefixes();
        test_path_join();
        test_fsck_exists();
        test_make_relative();
        test_strv_resolve();
        test_path_startswith();
        test_prefix_root();
        test_file_in_same_dir();
        test_last_path_component();
        test_path_extract_filename();
        test_filename_is_valid();
        test_hidden_or_backup_file();
        test_skip_dev_prefix();
        test_empty_or_root();
        test_path_startswith_set();
        test_path_startswith_strv();

        test_systemd_installation_has_version(argv[1]); /* NULL is OK */

        return 0;
}