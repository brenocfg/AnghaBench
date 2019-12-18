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
 int /*<<< orphan*/  test_config_parse_path_one (char*,char*) ; 

__attribute__((used)) static void test_config_parse_path(void) {
        test_config_parse_path_one("/path", "/path");
        test_config_parse_path_one("/path//////////", "/path");
        test_config_parse_path_one("///path/foo///bar////bar//", "/path/foo/bar/bar");
        test_config_parse_path_one("/path//./////hogehoge///.", "/path/hogehoge");
        test_config_parse_path_one("/path/\xc3\x80", "/path/\xc3\x80");

        test_config_parse_path_one("not_absolute/path", NULL);
        test_config_parse_path_one("/path/\xc3\x7f", NULL);
}