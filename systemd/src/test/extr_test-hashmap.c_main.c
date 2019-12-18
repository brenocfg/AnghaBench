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
 int /*<<< orphan*/  log_info (char*) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int /*<<< orphan*/  test_hashmap_funcs () ; 
 int /*<<< orphan*/  test_iterated_cache () ; 
 int /*<<< orphan*/  test_ordered_hashmap_funcs () ; 
 int /*<<< orphan*/  test_ordered_hashmap_next () ; 
 int /*<<< orphan*/  test_string_compare_func () ; 
 int /*<<< orphan*/  test_trivial_compare_func () ; 
 int /*<<< orphan*/  test_uint64_compare_func () ; 

int main(int argc, const char *argv[]) {
        /* This file tests in test-hashmap-plain.c, and tests in test-hashmap-ordered.c, which is generated
         * from test-hashmap-plain.c. Hashmap tests should be added to test-hashmap-plain.c, and here only if
         * they don't apply to ordered hashmaps. */

        log_parse_environment();
        log_open();

        test_hashmap_funcs();
        test_ordered_hashmap_funcs();

        log_info("/************ non-shared tests ************/");

        test_ordered_hashmap_next();
        test_uint64_compare_func();
        test_trivial_compare_func();
        test_string_compare_func();
        test_iterated_cache();

        return 0;
}