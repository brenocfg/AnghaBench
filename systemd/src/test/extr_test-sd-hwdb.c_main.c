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
 int log_tests_skipped_errno (int,char*) ; 
 int /*<<< orphan*/  test_basic_enumerate () ; 
 int test_failed_enumerate () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        int r;

        test_setup_logging(LOG_DEBUG);

        r = test_failed_enumerate();
        if (r < 0)
                return log_tests_skipped_errno(r, "cannot open hwdb");

        test_basic_enumerate();

        return 0;
}