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
 int string_has_cc (char*,char*) ; 

__attribute__((used)) static void test_string_has_cc(void) {
        assert_se(string_has_cc("abc\1", NULL));
        assert_se(string_has_cc("abc\x7f", NULL));
        assert_se(string_has_cc("abc\x7f", NULL));
        assert_se(string_has_cc("abc\t\x7f", "\t"));
        assert_se(string_has_cc("abc\t\x7f", "\t"));
        assert_se(string_has_cc("\x7f", "\t"));
        assert_se(string_has_cc("\x7f", "\t\a"));

        assert_se(!string_has_cc("abc\t\t", "\t"));
        assert_se(!string_has_cc("abc\t\t\a", "\t\a"));
        assert_se(!string_has_cc("a\ab\tc", "\t\a"));
}