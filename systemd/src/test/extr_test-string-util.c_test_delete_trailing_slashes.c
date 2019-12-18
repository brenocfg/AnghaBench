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
 int /*<<< orphan*/  delete_trailing_chars (char*,char*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_delete_trailing_slashes(void) {
        char s1[] = "foobar//",
             s2[] = "foobar/",
             s3[] = "foobar",
             s4[] = "";

        assert_se(streq(delete_trailing_chars(s1, "_"), "foobar//"));
        assert_se(streq(delete_trailing_chars(s1, "/"), "foobar"));
        assert_se(streq(delete_trailing_chars(s2, "/"), "foobar"));
        assert_se(streq(delete_trailing_chars(s3, "/"), "foobar"));
        assert_se(streq(delete_trailing_chars(s4, "/"), ""));
}