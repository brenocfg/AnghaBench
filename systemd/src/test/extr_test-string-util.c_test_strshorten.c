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
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strshorten (char*,int) ; 

__attribute__((used)) static void test_strshorten(void) {
        char s[] = "foobar";

        assert_se(strlen(strshorten(s, 6)) == 6);
        assert_se(strlen(strshorten(s, 12)) == 6);
        assert_se(strlen(strshorten(s, 2)) == 2);
        assert_se(strlen(strshorten(s, 0)) == 0);
}