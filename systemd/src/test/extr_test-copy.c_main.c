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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_copy_atomic () ; 
 int /*<<< orphan*/  test_copy_bytes () ; 
 int /*<<< orphan*/  test_copy_bytes_regular_file (char*,int,int) ; 
 int /*<<< orphan*/  test_copy_file () ; 
 int /*<<< orphan*/  test_copy_file_fd () ; 
 int /*<<< orphan*/  test_copy_tree () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_copy_file();
        test_copy_file_fd();
        test_copy_tree();
        test_copy_bytes();
        test_copy_bytes_regular_file(argv[0], false, (uint64_t) -1);
        test_copy_bytes_regular_file(argv[0], true, (uint64_t) -1);
        test_copy_bytes_regular_file(argv[0], false, 1000); /* smaller than copy buffer size */
        test_copy_bytes_regular_file(argv[0], true, 1000);
        test_copy_bytes_regular_file(argv[0], false, 32000); /* larger than copy buffer size */
        test_copy_bytes_regular_file(argv[0], true, 32000);
        test_copy_atomic();

        return 0;
}