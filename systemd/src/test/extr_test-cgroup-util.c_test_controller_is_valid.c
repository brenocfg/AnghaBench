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
 int cg_controller_is_valid (char*) ; 

__attribute__((used)) static void test_controller_is_valid(void) {
        assert_se(cg_controller_is_valid("foobar"));
        assert_se(cg_controller_is_valid("foo_bar"));
        assert_se(cg_controller_is_valid("name=foo"));
        assert_se(!cg_controller_is_valid(""));
        assert_se(!cg_controller_is_valid("name="));
        assert_se(!cg_controller_is_valid("="));
        assert_se(!cg_controller_is_valid("cpu,cpuacct"));
        assert_se(!cg_controller_is_valid("_"));
        assert_se(!cg_controller_is_valid("_foobar"));
        assert_se(!cg_controller_is_valid("tatü"));
}