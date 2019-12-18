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
 int /*<<< orphan*/  test_set_free_with_hash_ops () ; 
 int /*<<< orphan*/  test_set_put () ; 
 int /*<<< orphan*/  test_set_put_string_set () ; 
 int /*<<< orphan*/  test_set_steal_first () ; 

int main(int argc, const char *argv[]) {
        test_set_steal_first();
        test_set_free_with_hash_ops();
        test_set_put();
        test_set_put_string_set();

        return 0;
}