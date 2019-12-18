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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int load_and_print () ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 

int main(int argc, char *argv[]) {
        int r;

        log_parse_environment();
        log_open();

        if (argc > 1) {
                log_error("This program takes no arguments.");
                return EXIT_FAILURE;
        }

        r = load_and_print();
        if (r < 0)
                log_error_errno(r, "Failed to load environment.d: %m");

        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}