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
 int /*<<< orphan*/  fork_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_drop_privileges_dontkeep_net_raw ; 
 int /*<<< orphan*/  test_drop_privileges_fail ; 
 int /*<<< orphan*/  test_drop_privileges_keep_net_raw ; 

__attribute__((used)) static void test_drop_privileges(void) {
        fork_test(test_drop_privileges_keep_net_raw);
        fork_test(test_drop_privileges_dontkeep_net_raw);
        fork_test(test_drop_privileges_fail);
}