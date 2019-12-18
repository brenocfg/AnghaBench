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
 int documentation_url_is_valid (char*) ; 

__attribute__((used)) static void test_is_valid_documentation_url(void) {
        assert_se(documentation_url_is_valid("http://www.freedesktop.org/wiki/Software/systemd"));
        assert_se(documentation_url_is_valid("https://www.kernel.org/doc/Documentation/binfmt_misc.txt"));  /* dead */
        assert_se(documentation_url_is_valid("https://www.kernel.org/doc/Documentation/admin-guide/binfmt-misc.rst"));
        assert_se(documentation_url_is_valid("https://www.kernel.org/doc/html/latest/admin-guide/binfmt-misc.html"));
        assert_se(documentation_url_is_valid("file:/foo/foo"));
        assert_se(documentation_url_is_valid("man:systemd.special(7)"));
        assert_se(documentation_url_is_valid("info:bar"));

        assert_se(!documentation_url_is_valid("foo:"));
        assert_se(!documentation_url_is_valid("info:"));
        assert_se(!documentation_url_is_valid(""));
}