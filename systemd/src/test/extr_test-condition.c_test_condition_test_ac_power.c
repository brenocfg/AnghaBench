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
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_AC_POWER ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ condition_test (int /*<<< orphan*/ *) ; 
 scalar_t__ on_ac_power () ; 

__attribute__((used)) static void test_condition_test_ac_power(void) {
        Condition *condition;

        condition = condition_new(CONDITION_AC_POWER, "true", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == on_ac_power());
        condition_free(condition);

        condition = condition_new(CONDITION_AC_POWER, "false", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) != on_ac_power());
        condition_free(condition);

        condition = condition_new(CONDITION_AC_POWER, "false", false, true);
        assert_se(condition);
        assert_se(condition_test(condition) == on_ac_power());
        condition_free(condition);
}