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
 int /*<<< orphan*/  CONDITION_NULL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ condition_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_condition_test_null(void) {
        Condition *condition;

        condition = condition_new(CONDITION_NULL, NULL, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_NULL, NULL, false, true);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);
}