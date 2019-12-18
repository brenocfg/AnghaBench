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
 int /*<<< orphan*/  cellescape (char*,int,char*) ; 
 scalar_t__ is_locale_utf8 () ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_cellescape(void) {
        char buf[40];

        assert_se(streq(cellescape(buf, 1, ""), ""));
        assert_se(streq(cellescape(buf, 1, "1"), ""));
        assert_se(streq(cellescape(buf, 1, "12"), ""));

        assert_se(streq(cellescape(buf, 2, ""), ""));
        assert_se(streq(cellescape(buf, 2, "1"), "1"));
        assert_se(streq(cellescape(buf, 2, "12"), "."));
        assert_se(streq(cellescape(buf, 2, "123"), "."));

        assert_se(streq(cellescape(buf, 3, ""), ""));
        assert_se(streq(cellescape(buf, 3, "1"), "1"));
        assert_se(streq(cellescape(buf, 3, "12"), "12"));
        assert_se(streq(cellescape(buf, 3, "123"), ".."));
        assert_se(streq(cellescape(buf, 3, "1234"), ".."));

        assert_se(streq(cellescape(buf, 4, ""), ""));
        assert_se(streq(cellescape(buf, 4, "1"), "1"));
        assert_se(streq(cellescape(buf, 4, "12"), "12"));
        assert_se(streq(cellescape(buf, 4, "123"), "123"));
        assert_se(streq(cellescape(buf, 4, "1234"), is_locale_utf8() ? "…" : "..."));
        assert_se(streq(cellescape(buf, 4, "12345"), is_locale_utf8() ? "…" : "..."));

        assert_se(streq(cellescape(buf, 5, ""), ""));
        assert_se(streq(cellescape(buf, 5, "1"), "1"));
        assert_se(streq(cellescape(buf, 5, "12"), "12"));
        assert_se(streq(cellescape(buf, 5, "123"), "123"));
        assert_se(streq(cellescape(buf, 5, "1234"), "1234"));
        assert_se(streq(cellescape(buf, 5, "12345"), is_locale_utf8() ? "1…" : "1..."));
        assert_se(streq(cellescape(buf, 5, "123456"), is_locale_utf8() ? "1…" : "1..."));

        assert_se(streq(cellescape(buf, 1, "\020"), ""));
        assert_se(streq(cellescape(buf, 2, "\020"), "."));
        assert_se(streq(cellescape(buf, 3, "\020"), ".."));
        assert_se(streq(cellescape(buf, 4, "\020"), "…"));
        assert_se(streq(cellescape(buf, 5, "\020"), "\\020"));

        assert_se(streq(cellescape(buf, 5, "1234\020"), "1…"));
        assert_se(streq(cellescape(buf, 6, "1234\020"), "12…"));
        assert_se(streq(cellescape(buf, 7, "1234\020"), "123…"));
        assert_se(streq(cellescape(buf, 8, "1234\020"), "1234…"));
        assert_se(streq(cellescape(buf, 9, "1234\020"), "1234\\020"));

        assert_se(streq(cellescape(buf, 1, "\t\n"), ""));
        assert_se(streq(cellescape(buf, 2, "\t\n"), "."));
        assert_se(streq(cellescape(buf, 3, "\t\n"), ".."));
        assert_se(streq(cellescape(buf, 4, "\t\n"), "…"));
        assert_se(streq(cellescape(buf, 5, "\t\n"), "\\t\\n"));

        assert_se(streq(cellescape(buf, 5, "1234\t\n"), "1…"));
        assert_se(streq(cellescape(buf, 6, "1234\t\n"), "12…"));
        assert_se(streq(cellescape(buf, 7, "1234\t\n"), "123…"));
        assert_se(streq(cellescape(buf, 8, "1234\t\n"), "1234…"));
        assert_se(streq(cellescape(buf, 9, "1234\t\n"), "1234\\t\\n"));

        assert_se(streq(cellescape(buf, 4, "x\t\020\n"), "…"));
        assert_se(streq(cellescape(buf, 5, "x\t\020\n"), "x…"));
        assert_se(streq(cellescape(buf, 6, "x\t\020\n"), "x…"));
        assert_se(streq(cellescape(buf, 7, "x\t\020\n"), "x\\t…"));
        assert_se(streq(cellescape(buf, 8, "x\t\020\n"), "x\\t…"));
        assert_se(streq(cellescape(buf, 9, "x\t\020\n"), "x\\t…"));
        assert_se(streq(cellescape(buf, 10, "x\t\020\n"), "x\\t\\020\\n"));

        assert_se(streq(cellescape(buf, 6, "1\011"), "1\\t"));
        assert_se(streq(cellescape(buf, 6, "1\020"), "1\\020"));
        assert_se(streq(cellescape(buf, 6, "1\020x"), is_locale_utf8() ? "1…" : "1..."));

        assert_se(streq(cellescape(buf, 40, "1\020"), "1\\020"));
        assert_se(streq(cellescape(buf, 40, "1\020x"), "1\\020x"));

        assert_se(streq(cellescape(buf, 40, "\a\b\f\n\r\t\v\\\"'"), "\\a\\b\\f\\n\\r\\t\\v\\\\\\\"\\'"));
        assert_se(streq(cellescape(buf, 6, "\a\b\f\n\r\t\v\\\"'"), is_locale_utf8() ? "\\a…" : "\\a..."));
        assert_se(streq(cellescape(buf, 7, "\a\b\f\n\r\t\v\\\"'"), is_locale_utf8() ? "\\a…" : "\\a..."));
        assert_se(streq(cellescape(buf, 8, "\a\b\f\n\r\t\v\\\"'"), is_locale_utf8() ? "\\a\\b…" : "\\a\\b..."));

        assert_se(streq(cellescape(buf, sizeof buf, "1\020"), "1\\020"));
        assert_se(streq(cellescape(buf, sizeof buf, "1\020x"), "1\\020x"));
}