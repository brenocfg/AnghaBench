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
typedef  int usec_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int slow_tests_enabled () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  watchdog_close (int) ; 
 int watchdog_ping () ; 
 int watchdog_set_timeout (int*) ; 

int main(int argc, char *argv[]) {
        usec_t t;
        unsigned i, count;
        int r;
        bool slow;

        test_setup_logging(LOG_DEBUG);

        slow = slow_tests_enabled();

        t = slow ? 10 * USEC_PER_SEC : 1 * USEC_PER_SEC;
        count = slow ? 5 : 3;

        r = watchdog_set_timeout(&t);
        if (r < 0)
                log_warning_errno(r, "Failed to open watchdog: %m");
        if (r == -EPERM)
                t = 0;

        for (i = 0; i < count; i++) {
                log_info("Pinging...");
                r = watchdog_ping();
                if (r < 0)
                        log_warning_errno(r, "Failed to ping watchdog: %m");

                usleep(t/2);
        }

        watchdog_close(true);
        return 0;
}