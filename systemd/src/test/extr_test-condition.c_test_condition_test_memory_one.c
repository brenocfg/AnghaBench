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
 int /*<<< orphan*/  CONDITION_MEMORY ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,char const*,int,int) ; 
 int condition_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  condition_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void test_condition_test_memory_one(const char *s, bool result) {
        Condition *condition;
        int r;

        log_debug("%s=%s", condition_type_to_string(CONDITION_MEMORY), s);

        condition = condition_new(CONDITION_MEMORY, s, false, false);
        assert_se(condition);

        r = condition_test(condition);
        assert_se(r >= 0);
        assert_se(r == result);
        condition_free(condition);
}