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
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int arg_keep ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  setup_interleaved ; 
 int /*<<< orphan*/  setup_sequential ; 
 int /*<<< orphan*/  test_sequence_numbers () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_skip (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        /* journal_file_open requires a valid machine id */
        if (access("/etc/machine-id", F_OK) != 0)
                return log_tests_skipped("/etc/machine-id not found");

        arg_keep = argc > 1;

        test_skip(setup_sequential);
        test_skip(setup_interleaved);

        test_sequence_numbers();

        return 0;
}