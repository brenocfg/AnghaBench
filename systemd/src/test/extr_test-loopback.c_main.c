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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int loopback_setup () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char* argv[]) {
        int r;

        test_setup_logging(LOG_DEBUG);

        r = loopback_setup();
        if (r < 0)
                log_error_errno(r, "loopback: %m");

        return r >= 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}