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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  log_warning (char*) ; 
 int test_fiemap (char*) ; 
 int /*<<< orphan*/  test_parse_sleep_config () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_sleep () ; 

int main(int argc, char* argv[]) {
        int i, r = 0, k;

        test_setup_logging(LOG_DEBUG);

        if (getuid() != 0)
                log_warning("This program is unlikely to work for unprivileged users");

        test_parse_sleep_config();
        test_sleep();

        if (argc <= 1)
                assert_se(test_fiemap(argv[0]) == 0);
        else
                for (i = 1; i < argc; i++) {
                        k = test_fiemap(argv[i]);
                        if (r == 0)
                                r = k;
                }

        return r;
}