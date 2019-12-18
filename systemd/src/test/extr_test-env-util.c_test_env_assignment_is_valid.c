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
 int env_assignment_is_valid (char*) ; 

__attribute__((used)) static void test_env_assignment_is_valid(void) {
        assert_se(env_assignment_is_valid("a="));
        assert_se(env_assignment_is_valid("b=głąb kapuściany"));
        assert_se(env_assignment_is_valid("c=\\007\\009\\011"));
        assert_se(env_assignment_is_valid("e=printf \"\\x1b]0;<mock-chroot>\\x07<mock-chroot>\""));
        assert_se(env_assignment_is_valid("f=tab\tcharacter"));
        assert_se(env_assignment_is_valid("g=new\nline"));

        assert_se(!env_assignment_is_valid("="));
        assert_se(!env_assignment_is_valid("a b="));
        assert_se(!env_assignment_is_valid("a ="));
        assert_se(!env_assignment_is_valid(" b="));
        /* no dots or dashes: http://tldp.org/LDP/abs/html/gotchas.html */
        assert_se(!env_assignment_is_valid("a.b="));
        assert_se(!env_assignment_is_valid("a-b="));
        assert_se(!env_assignment_is_valid("\007=głąb kapuściany"));
        assert_se(!env_assignment_is_valid("c\009=\007\009\011"));
        assert_se(!env_assignment_is_valid("głąb=printf \"\x1b]0;<mock-chroot>\x07<mock-chroot>\""));
}