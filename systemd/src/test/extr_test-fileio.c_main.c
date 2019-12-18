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
 int /*<<< orphan*/  test_capeff () ; 
 int /*<<< orphan*/  test_executable_is_script () ; 
 int /*<<< orphan*/  test_fgetc () ; 
 int /*<<< orphan*/  test_load_env_file_pairs () ; 
 int /*<<< orphan*/  test_merge_env_file () ; 
 int /*<<< orphan*/  test_merge_env_file_invalid () ; 
 int /*<<< orphan*/  test_parse_env_file () ; 
 int /*<<< orphan*/  test_parse_multiline_env_file () ; 
 int /*<<< orphan*/  test_read_line () ; 
 int /*<<< orphan*/  test_read_line2 () ; 
 int /*<<< orphan*/  test_read_line3 () ; 
 int /*<<< orphan*/  test_read_line4 () ; 
 int /*<<< orphan*/  test_read_nul_string () ; 
 int /*<<< orphan*/  test_search_and_fopen () ; 
 int /*<<< orphan*/  test_search_and_fopen_nulstr () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_status_field () ; 
 int /*<<< orphan*/  test_tempfn () ; 
 int /*<<< orphan*/  test_write_string_file () ; 
 int /*<<< orphan*/  test_write_string_file_no_create () ; 
 int /*<<< orphan*/  test_write_string_file_verify () ; 
 int /*<<< orphan*/  test_write_string_stream () ; 
 int /*<<< orphan*/  test_writing_tmpfile () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_parse_env_file();
        test_parse_multiline_env_file();
        test_merge_env_file();
        test_merge_env_file_invalid();
        test_executable_is_script();
        test_status_field();
        test_capeff();
        test_write_string_stream();
        test_write_string_file();
        test_write_string_file_no_create();
        test_write_string_file_verify();
        test_load_env_file_pairs();
        test_search_and_fopen();
        test_search_and_fopen_nulstr();
        test_writing_tmpfile();
        test_tempfn();
        test_fgetc();
        test_read_line();
        test_read_line2();
        test_read_line3();
        test_read_line4();
        test_read_nul_string();

        return 0;
}