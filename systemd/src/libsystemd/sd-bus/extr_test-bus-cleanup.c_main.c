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
 int /*<<< orphan*/  LOG_INFO ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  test_bus_new () ; 
 int /*<<< orphan*/  test_bus_new_method_call () ; 
 int /*<<< orphan*/  test_bus_new_signal () ; 
 scalar_t__ test_bus_open () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_INFO);

        test_bus_new();

        if (test_bus_open() < 0)
                return log_tests_skipped("Failed to connect to bus");

        test_bus_new_method_call();
        test_bus_new_signal();

        return EXIT_SUCCESS;
}