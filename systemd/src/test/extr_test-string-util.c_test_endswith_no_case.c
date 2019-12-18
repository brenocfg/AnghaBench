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
 int endswith_no_case (char*,char*) ; 

__attribute__((used)) static void test_endswith_no_case(void) {
        assert_se(endswith_no_case("fooBAR", "bar"));
        assert_se(endswith_no_case("foobar", ""));
        assert_se(endswith_no_case("foobar", "FOOBAR"));
        assert_se(endswith_no_case("", ""));

        assert_se(!endswith_no_case("foobar", "FOO"));
        assert_se(!endswith_no_case("foobar", "FOOBARFOOFOO"));
}