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
 int /*<<< orphan*/  WHITESPACE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 char* delete_chars (char*,int /*<<< orphan*/ ) ; 
 int streq (char*,char*) ; 

__attribute__((used)) static void test_delete_chars(void) {
        char *s, input[] = "   hello, waldo.   abc";

        s = delete_chars(input, WHITESPACE);
        assert_se(streq(s, "hello,waldo.abc"));
        assert_se(s == input);
}