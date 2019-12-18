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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ geteuid () ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  test_chown_recursive () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        if (geteuid() != 0)
                return log_tests_skipped("not running as root");

        test_chown_recursive();

        return EXIT_SUCCESS;
}