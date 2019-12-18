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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_leading_chars (char*,char*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_skip_leading_chars(void) {
        char input1[] = " \n \r k \n \r ",
                input2[] = "kkkkthiskkkiskkkaktestkkk",
                input3[] = "abcdef";

        assert_se(streq(skip_leading_chars(input1, WHITESPACE), "k \n \r "));
        assert_se(streq(skip_leading_chars(input2, "k"), "thiskkkiskkkaktestkkk"));
        assert_se(streq(skip_leading_chars(input2, "tk"), "hiskkkiskkkaktestkkk"));
        assert_se(streq(skip_leading_chars(input3, WHITESPACE), "abcdef"));
        assert_se(streq(skip_leading_chars(input3, "bcaef"), "def"));
}