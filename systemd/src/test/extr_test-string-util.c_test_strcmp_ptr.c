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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ strcmp_ptr (char*,char*) ; 

__attribute__((used)) static void test_strcmp_ptr(void) {
        assert_se(strcmp_ptr(NULL, NULL) == 0);
        assert_se(strcmp_ptr("", NULL) > 0);
        assert_se(strcmp_ptr("foo", NULL) > 0);
        assert_se(strcmp_ptr(NULL, "") < 0);
        assert_se(strcmp_ptr(NULL, "bar") < 0);
        assert_se(strcmp_ptr("foo", "bar") > 0);
        assert_se(strcmp_ptr("bar", "baz") < 0);
        assert_se(strcmp_ptr("foo", "foo") == 0);
        assert_se(strcmp_ptr("", "") == 0);
}