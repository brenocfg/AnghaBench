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
 int /*<<< orphan*/  STRV_MAKE (char*,...) ; 
 int /*<<< orphan*/  STRV_MAKE_EMPTY ; 
 int /*<<< orphan*/  test_config_parse_strv_one (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_config_parse_strv(void) {
        test_config_parse_strv_one("", STRV_MAKE_EMPTY);
        test_config_parse_strv_one("foo", STRV_MAKE("foo"));
        test_config_parse_strv_one("foo bar foo", STRV_MAKE("foo", "bar", "foo"));
        test_config_parse_strv_one("\"foo bar\" foo", STRV_MAKE("foo bar", "foo"));
        test_config_parse_strv_one("\xc3\x80", STRV_MAKE("\xc3\x80"));
        test_config_parse_strv_one("\xc3\x7f", STRV_MAKE("\xc3\x7f"));
}