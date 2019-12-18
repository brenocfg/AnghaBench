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
 int /*<<< orphan*/  test_proc_cmdline_get_bool () ; 
 int /*<<< orphan*/  test_proc_cmdline_get_key () ; 
 int /*<<< orphan*/  test_proc_cmdline_get_key_many () ; 
 int /*<<< orphan*/  test_proc_cmdline_given (int) ; 
 int /*<<< orphan*/  test_proc_cmdline_key_startswith () ; 
 int /*<<< orphan*/  test_proc_cmdline_key_streq () ; 
 int /*<<< orphan*/  test_proc_cmdline_override () ; 
 int /*<<< orphan*/  test_proc_cmdline_parse () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(void) {
        test_setup_logging(LOG_INFO);

        test_proc_cmdline_parse();
        test_proc_cmdline_override();
        test_proc_cmdline_given(false);
        /* Repeat the same thing, but now flip our ininitrdness */
        test_proc_cmdline_given(true);
        test_proc_cmdline_key_streq();
        test_proc_cmdline_key_startswith();
        test_proc_cmdline_get_key();
        test_proc_cmdline_get_bool();
        test_proc_cmdline_get_key_many();

        return 0;
}