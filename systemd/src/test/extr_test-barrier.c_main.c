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
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int VIRTUALIZATION_NONE ; 
 int detect_virtualization () ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  slow_tests_enabled () ; 
 int /*<<< orphan*/  test_barrier_exit () ; 
 int /*<<< orphan*/  test_barrier_no_exit () ; 
 int /*<<< orphan*/  test_barrier_pending_exit () ; 
 int /*<<< orphan*/  test_barrier_sync () ; 
 int /*<<< orphan*/  test_barrier_sync_next () ; 
 int /*<<< orphan*/  test_barrier_sync_next_local () ; 
 int /*<<< orphan*/  test_barrier_sync_next_local_abort () ; 
 int /*<<< orphan*/  test_barrier_wait_abortion () ; 
 int /*<<< orphan*/  test_barrier_wait_abortion_local () ; 
 int /*<<< orphan*/  test_barrier_wait_abortion_local_unmatched () ; 
 int /*<<< orphan*/  test_barrier_wait_abortion_unmatched () ; 
 int /*<<< orphan*/  test_barrier_wait_next () ; 
 int /*<<< orphan*/  test_barrier_wait_next_twice () ; 
 int /*<<< orphan*/  test_barrier_wait_next_twice_local () ; 
 int /*<<< orphan*/  test_barrier_wait_next_twice_local_sync () ; 
 int /*<<< orphan*/  test_barrier_wait_next_twice_sync () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        int v;
        test_setup_logging(LOG_INFO);

        if (!slow_tests_enabled())
                return log_tests_skipped("slow tests are disabled");

        /*
         * This test uses real-time alarms and sleeps to test for CPU races
         * explicitly. This is highly fragile if your system is under load. We
         * already increased the BASE_TIME value to make the tests more robust,
         * but that just makes the test take significantly longer. Given the recent
         * issues when running the test in a virtualized environments, limit it
         * to bare metal machines only, to minimize false-positives in CIs.
         */
        v = detect_virtualization();
        if (IN_SET(v, -EPERM, -EACCES))
                return log_tests_skipped("Cannot detect virtualization");

        if (v != VIRTUALIZATION_NONE)
                return log_tests_skipped("This test requires a baremetal machine");

        test_barrier_sync();
        test_barrier_wait_next();
        test_barrier_wait_next_twice();
        test_barrier_wait_next_twice_sync();
        test_barrier_wait_next_twice_local();
        test_barrier_wait_next_twice_local_sync();
        test_barrier_sync_next();
        test_barrier_sync_next_local();
        test_barrier_sync_next_local_abort();
        test_barrier_wait_abortion();
        test_barrier_wait_abortion_unmatched();
        test_barrier_wait_abortion_local();
        test_barrier_wait_abortion_local_unmatched();
        test_barrier_exit();
        test_barrier_no_exit();
        test_barrier_pending_exit();

        return 0;
}