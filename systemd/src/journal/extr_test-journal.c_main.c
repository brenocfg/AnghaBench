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
 int /*<<< orphan*/  LOG_INFO ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int arg_keep ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  test_empty () ; 
 int /*<<< orphan*/  test_min_compress_size () ; 
 int /*<<< orphan*/  test_non_empty () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        arg_keep = argc > 1;

        test_setup_logging(LOG_INFO);

        /* journal_file_open requires a valid machine id */
        if (access("/etc/machine-id", F_OK) != 0)
                return log_tests_skipped("/etc/machine-id not found");

        test_non_empty();
        test_empty();
#if HAVE_XZ || HAVE_LZ4
        test_min_compress_size();
#endif

        return 0;
}