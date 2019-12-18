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
struct utsname {char const* release; } ;
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_KERNEL_VERSION ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  condition_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 char* strjoina (char*,char const*) ; 
 int /*<<< orphan*/  strshorten (char const*,int) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void test_condition_test_kernel_version(void) {
        Condition *condition;
        struct utsname u;
        const char *v;

        condition = condition_new(CONDITION_KERNEL_VERSION, "*thisreallyshouldntbeinthekernelversion*", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "*", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        /* An artificially empty condition. It evaluates to true, but normally
         * such condition cannot be created, because the condition list is reset instead. */
        condition = condition_new(CONDITION_KERNEL_VERSION, "", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        assert_se(uname(&u) >= 0);

        condition = condition_new(CONDITION_KERNEL_VERSION, u.release, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        strshorten(u.release, 4);
        strcpy(strchr(u.release, 0), "*");

        condition = condition_new(CONDITION_KERNEL_VERSION, u.release, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        /* 0.1.2 would be a very very very old kernel */
        condition = condition_new(CONDITION_KERNEL_VERSION, "> 0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, ">0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "'>0.1.2' '<9.0.0'", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "> 0.1.2 < 9.0.0", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == -EINVAL);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, ">", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == -EINVAL);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, ">= 0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "< 0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "<= 0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "= 0.1.2", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        /* 4711.8.15 is a very very very future kernel */
        condition = condition_new(CONDITION_KERNEL_VERSION, "< 4711.8.15", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "<= 4711.8.15", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "= 4711.8.15", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, "> 4711.8.15", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_KERNEL_VERSION, ">= 4711.8.15", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        assert_se(uname(&u) >= 0);

        v = strjoina(">=", u.release);
        condition = condition_new(CONDITION_KERNEL_VERSION, v, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        v = strjoina("=  ", u.release);
        condition = condition_new(CONDITION_KERNEL_VERSION, v, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        v = strjoina("<=", u.release);
        condition = condition_new(CONDITION_KERNEL_VERSION, v, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        v = strjoina("> ", u.release);
        condition = condition_new(CONDITION_KERNEL_VERSION, v, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        v = strjoina("<   ", u.release);
        condition = condition_new(CONDITION_KERNEL_VERSION, v, false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);
}