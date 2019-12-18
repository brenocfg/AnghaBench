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
 int /*<<< orphan*/  strv_skip (char**,int) ; 
 int /*<<< orphan*/  test_runlevel_to_target () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_unit_file_build_name_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_unit_validate_alias_symlink_and_warn () ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_DEBUG);

        test_unit_validate_alias_symlink_and_warn();
        test_unit_file_build_name_map(strv_skip(argv, 1));
        test_runlevel_to_target();

        return 0;
}