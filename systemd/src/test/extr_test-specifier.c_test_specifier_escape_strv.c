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
 int /*<<< orphan*/ * STRV_MAKE (char*,...) ; 
 int /*<<< orphan*/  test_specifier_escape_strv_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_specifier_escape_strv(void) {
        test_specifier_escape_strv_one(NULL, NULL);
        test_specifier_escape_strv_one(STRV_MAKE(NULL), STRV_MAKE(NULL));
        test_specifier_escape_strv_one(STRV_MAKE(""), STRV_MAKE(""));
        test_specifier_escape_strv_one(STRV_MAKE("foo"), STRV_MAKE("foo"));
        test_specifier_escape_strv_one(STRV_MAKE("%"), STRV_MAKE("%%"));
        test_specifier_escape_strv_one(STRV_MAKE("foo", "%", "foo%", "%foo", "foo%foo", "quux", "%%%"), STRV_MAKE("foo", "%%", "foo%%", "%%foo", "foo%%foo", "quux", "%%%%%%"));
}