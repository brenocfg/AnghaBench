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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  test_GREEDY_REALLOC () ; 
 int /*<<< orphan*/  test_alloca () ; 
 int /*<<< orphan*/  test_auto_erase_memory () ; 
 int /*<<< orphan*/  test_bool_assign () ; 
 int /*<<< orphan*/  test_cleanup_order () ; 
 int /*<<< orphan*/  test_memdup_multiply_and_greedy_realloc () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_alloca();
        test_GREEDY_REALLOC();
        test_memdup_multiply_and_greedy_realloc();
        test_bool_assign();
        test_cleanup_order();
        test_auto_erase_memory();

        return 0;
}