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
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 scalar_t__ streq_ptr (char*,char*) ; 
 int /*<<< orphan*/  test_login () ; 
 int /*<<< orphan*/  test_monitor () ; 

int main(int argc, char* argv[]) {
        log_parse_environment();
        log_open();

        log_info("/* Information printed is from the live system */");

        test_login();

        if (streq_ptr(argv[1], "-m"))
                test_monitor();

        return 0;
}