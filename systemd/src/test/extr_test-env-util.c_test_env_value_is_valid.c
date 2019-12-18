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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_value_is_valid (char*) ; 

__attribute__((used)) static void test_env_value_is_valid(void) {
        assert_se(env_value_is_valid(""));
        assert_se(env_value_is_valid("głąb kapuściany"));
        assert_se(env_value_is_valid("printf \"\\x1b]0;<mock-chroot>\\x07<mock-chroot>\""));
        assert_se(env_value_is_valid("tab\tcharacter"));
        assert_se(env_value_is_valid("new\nline"));
}