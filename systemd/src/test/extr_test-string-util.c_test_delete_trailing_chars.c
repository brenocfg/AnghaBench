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
 char* WHITESPACE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 char* delete_trailing_chars (char*,char*) ; 
 int streq (char*,char*) ; 

__attribute__((used)) static void test_delete_trailing_chars(void) {

        char *s,
                input1[] = " \n \r k \n \r ",
                input2[] = "kkkkthiskkkiskkkaktestkkk",
                input3[] = "abcdef";

        s = delete_trailing_chars(input1, WHITESPACE);
        assert_se(streq(s, " \n \r k"));
        assert_se(s == input1);

        s = delete_trailing_chars(input2, "kt");
        assert_se(streq(s, "kkkkthiskkkiskkkaktes"));
        assert_se(s == input2);

        s = delete_trailing_chars(input3, WHITESPACE);
        assert_se(streq(s, "abcdef"));
        assert_se(s == input3);

        s = delete_trailing_chars(input3, "fe");
        assert_se(streq(s, "abcd"));
        assert_se(s == input3);
}