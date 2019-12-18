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
 int /*<<< orphan*/  TEST_REQ_RUNNING_SYSTEMD (int) ; 
 int test_default_memory_low () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char* argv[]) {
        int rc = EXIT_SUCCESS;

        test_setup_logging(LOG_DEBUG);

        TEST_REQ_RUNNING_SYSTEMD(rc = test_default_memory_low());

        return rc;
}